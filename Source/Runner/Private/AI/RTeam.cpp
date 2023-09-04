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

bool ARTeam::GetLocationOnCircle(FVector& Result, ARAICharacter* Char) const
{
    if (CharactersHasAlreadyTakenPlaceOnCircle.Contains(Char))
    {
        Result = CharactersHasAlreadyTakenPlaceOnCircle[Char];
        return true;
    }
    return false;
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
        UE_LOG(LogRAITeam, Display, TEXT("DistibuteAllPointsBetweenAI:  %s for %s"),*Result.ToString(),  *AICharacter->GetController()->GetName());
    
    }
}

void ARTeam::TakeLocationOnCircle(FVector& Result, ARAICharacter* Char)
{
    if (CharactersHasAlreadyTakenPlaceOnCircle.Contains(Char))
    {
        return;
    }
    if (AllFreePointsOnCircle.Num() == 0)
    {
        return;
    }
    CriticalSection.Lock();
    Result = AllFreePointsOnCircle.Pop();
    CharactersHasAlreadyTakenPlaceOnCircle.Add(Char, Result);
    CriticalSection.Unlock();
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
    CriticalSection.Lock();
    UE_LOG(LogRAITeam, Display, TEXT("ClearCircleAroundCharacter"));
    bCircleExist = false;
    AllFreePointsOnCircle.Empty();
    TotalNumberOfPointsOnCircle = 0;
    CharactersHasAlreadyTakenPlaceOnCircle.Empty();
    CriticalSection.Unlock();
}

void ARTeam::OnPickableUpActorStateWasChanged(ERPickableItemState NewState)
{
    if (NewState == ERPickableItemState::OutsideCircle)
    {
        ClearCircleAroundCharacter();
    }
}
