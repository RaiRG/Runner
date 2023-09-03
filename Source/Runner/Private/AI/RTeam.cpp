// Runner Game, All Rights Reserved.


#include "RTeam.h"

#include "RAICharacter.h"
#include "RPickableItem.h"
#include "RPlayerCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogRAITeam, All, All);

void ARTeam::AddAIMember(ARAICharacter* NewMember)
{
    if (!NewMember->GetTeam() && NewMember)
    {
        AllMembers.AddUnique(NewMember);
        NewMember->SetTeam(this);
    }
}

bool ARTeam::TakeLocationOnCircle(FVector& Result, ARAICharacter* Char)
{
    UE_LOG(LogRAITeam, Display, TEXT("GetLocationOnShape"));
    if (CharactersHasAlreadyTakenPlaceOnCircle.Contains(Char))
    {
        Result = CharactersHasAlreadyTakenPlaceOnCircle[Char];
        return true;
    }
    if (AllFreePointsOnCircle.Num() == 0)
    {
        UE_LOG(LogRAITeam, Display, TEXT("GAllFreePointsOnCircle.Num is zero for %s"), *Char->GetName());
        return false;
    }
    CriticalSection.Lock();
    Result = AllFreePointsOnCircle.Pop();
    CharactersHasAlreadyTakenPlaceOnCircle.Add(Char, Result);
    CriticalSection.Unlock();
    return true;
}


bool ARTeam::IsEveryoneInCircle() const
{
    if (!bCircleExist)
    {
        return false;
    }
    int32 NumberOfCharactersInCircle = 0;
    for (const auto Member : AllMembers)
    {
        if (Member->GetStandsInCircle())
        {
            NumberOfCharactersInCircle++;
        }
    }
    return NumberOfCharactersInCircle == TotalNumberOfPointsOnCircle;
}

bool ARTeam::IsPointInsideCircle(FVector Point) const
{
    if (bCircleExist)
    {
        UE_LOG(LogRAITeam, Display, TEXT("CurrentCenterOfCircle %s, Position %s, Distance %f, CircleRadius %f"),
            *CurrentCenterOfCircle.ToString(), *Point.ToString(),
            FVector::Distance(CurrentCenterOfCircle, Point), CircleRadius);
    }
    else
    {
        UE_LOG(LogRAITeam, Display, TEXT("Circle doesn't exist"));
    }
    return bCircleExist && FVector::Distance(CurrentCenterOfCircle, Point) <= CircleRadius;
}

void ARTeam::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> AllAICharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARAICharacter::StaticClass(), AllAICharacters);
    for (const auto AIActor : AllAICharacters)
    {
        if (const auto AICharacter = Cast<ARAICharacter>(AIActor))
        {
            AddAIMember(AICharacter);
        }
    }

    PlayerCharacter = Cast<ARPlayerCharacter>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ARPlayerCharacter::StaticClass()));
    if (PlayerCharacter)
    {
        PlayerCharacter->PlayerCharacterChangeMovementState.AddDynamic(
            this, &ARTeam::OnPlayerCharacterChangeMovementState);
    }

    PickableItem = Cast<ARPickableItem>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ARPickableItem::StaticClass()));
    if (PickableItem)
    {
        PickableItem->PickableUpActorChangeState.AddDynamic(this, &ARTeam::OnPickableUpActorStateWasChanged);
    }
}

void ARTeam::OnPlayerCharacterChangeMovementState(ERPlayerCharacterState MovementState)
{
    if (MovementState == ERPlayerCharacterState::MovementBlocked)
    {
        if (AllMembers.Num() > 0)
        {
            BuildCircleAroundCharacter();
        }
    }
}

void ARTeam::OnFindAllPossiblePoints(TSharedPtr<FEnvQueryResult> Result)
{
    bCircleExist = true;
    AllFreePointsOnCircle.Empty();
    Result->GetAllAsLocations(AllFreePointsOnCircle);
    TotalNumberOfPointsOnCircle = AllFreePointsOnCircle.Num();
    DistibuteAllPointsBetweenAI();
    UE_LOG(LogRAITeam, Display, TEXT("TotalNumberOfPointsOnCircle = %i"),TotalNumberOfPointsOnCircle );
    CriticalSection.Unlock();
}

void ARTeam::DistibuteAllPointsBetweenAI()
{
    if (bPrioritizeCharacterWithPickableItem)
    {
        auto GrabbingCharacter = GetHoldedObjectCharacter();
        FVector Result;
        TakeLocationOnCircle(Result, GrabbingCharacter);
    }
    for (auto AICharacter : AllMembers)
    {
        FVector Result;
        TakeLocationOnCircle(Result, AICharacter);
    }
}

ARAICharacter* ARTeam::GetHoldedObjectCharacter()
{
    if (!PickableItem)
    {
        return nullptr;
    }

    return Cast<ARAICharacter>(PickableItem->GetGrabbingActor());
}

void ARTeam::BuildCircleAroundCharacter()
{
    UE_LOG(LogRAITeam, Display, TEXT("OnPlayerCharacterChangeMovementState"));
    CriticalSection.Lock();
    if (PlayerCharacter)
    {
        CurrentCenterOfCircle = PlayerCharacter->GetActorLocation();
    }

    FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EnvQueryForBotsStandingShape);
    HidingSpotQueryRequest.Execute(
        EEnvQueryRunMode::AllMatching,
        this,
        &ARTeam::OnFindAllPossiblePoints);
}

void ARTeam::ClearCircleAroundCharacter()
{
    UE_LOG(LogRAITeam, Display, TEXT("ClearCircleAroundCharacter"));
    bCircleExist = false;
    AllFreePointsOnCircle.Empty();
    TotalNumberOfPointsOnCircle = 0;
    CharactersHasAlreadyTakenPlaceOnCircle.Empty();
}

void ARTeam::OnPickableUpActorStateWasChanged(ERPickableItemState NewState)
{
    if (NewState == ERPickableItemState::OutsideCircle)
    {
        ClearCircleAroundCharacter();
    }
}
