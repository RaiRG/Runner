// Runner Game, All Rights Reserved.


#include "RTeam.h"

#include "NavigationSystem.h"
#include "RAICharacter.h"
#include "RPickableItem.h"
#include "RPlayerCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogRAITeam, All, All);

DEFINE_LOG_CATEGORY_STATIC(LogRAITeamCircle, All, All);

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
        UE_LOG(LogRAITeamCircle, Warning, TEXT("CircleDoesn't Exist"));
        return false;
    }
    int32 NumberOfCharactersInCircle = 0;
    for (const auto Member : AllMembers)
    {
        if (Member->GetStandsInCircle())
        {
            NumberOfCharactersInCircle++;
            UE_LOG(LogRAITeamCircle, Display, TEXT("%s stands in circle"), *Member->GetController()->GetName());
        }
        else
        {
            UE_LOG(LogRAITeamCircle, Display, TEXT("%s NOT stands in circle"), *Member->GetController()->GetName());

        }
    }
    UE_LOG(LogRAITeamCircle, Display, TEXT("NumberOfCharactersInCircle = %i, TotalNumberOfPointsOnCircle = %i, AllMembers.Num() %i"), NumberOfCharactersInCircle,
        TotalNumberOfPointsOnCircle, AllMembers.Num());
    return TotalNumberOfPointsOnCircle <= AllMembers.Num()
               ? NumberOfCharactersInCircle == TotalNumberOfPointsOnCircle
               : NumberOfCharactersInCircle == AllMembers.Num();
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
    CharactersHasAlreadyTakenPlaceOnCircle.Empty();
    int32 Num = 0;
    for (auto Item : Result->Items)
    {
        UE_LOG(LogRAITeamCircle, Display, TEXT("Index %i Item Score = %f"), Num, Item.Score);
        Num++;

    }
    DistributeAllPointsBetweenAI();
    UE_LOG(LogRAITeam, Display, TEXT("TotalNumberOfPointsOnCircle = %i"), TotalNumberOfPointsOnCircle);
    CriticalSection.Unlock();
}

void ARTeam::DistributeAllPointsBetweenAI()
{
    const auto GrabbingCharacter = GetHoldedObjectCharacter();
    auto AssignedNumber = 0;
    for (const auto AICharacter : AllMembers)
    {
        if (AICharacter == GrabbingCharacter)
        {
            continue;
        }
        auto WasAssigned = AssignSuitablePointOnCircleToAI(AICharacter);
        if (WasAssigned)
        {
            AssignedNumber++;
        }
        if (TotalNumberOfPointsOnCircle - AssignedNumber == 1)
        {
            break;
        }
    }
    AssignSuitablePointOnCircleToAI(GrabbingCharacter);

}

bool ARTeam::GetSuitablePointOnCircle(FVector& SuitablePointOnCircle, const ARAICharacter* Character) const
{
    if (CharactersHasAlreadyTakenPlaceOnCircle.Contains(Character))
    {
        SuitablePointOnCircle = CharactersHasAlreadyTakenPlaceOnCircle[Character];
        return true;
    }

    if (Character)
    {

        for (const FVector Point : AllFreePointsOnCircle)
        {
            if (IsPointReachableByCharacter(Point, Character))
            {
                SuitablePointOnCircle = Point;
                return true;
            }
        }
    }
    return false;
}

bool ARTeam::IsPointReachableByCharacter(const FVector Point, const ARAICharacter* Character) const
{
    const FVector BotLocation = Character->GetActorLocation();
    const auto NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    const ANavigationData* NavData = Character
                                         ? NavSys->GetNavDataForProps(Character->GetNavAgentPropertiesRef(),
                                             Character->GetNavAgentLocation())
                                         : NULL;
    TSubclassOf<UNavigationQueryFilter> FilterClass;
    FSharedConstNavQueryFilter QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, Character, FilterClass);
    return NavSys->TestPathSync(FPathFindingQuery(this, *NavData, BotLocation, Point, QueryFilter), EPathFindingMode::Hierarchical);

}

void ARTeam::AssignPointToAI(FVector Point, ARAICharacter* Character)
{
    if (CharactersHasAlreadyTakenPlaceOnCircle.Contains(Character))
    {
        return;
    }

    CriticalSection.Lock();
    AllFreePointsOnCircle.Remove(Point);
    CharactersHasAlreadyTakenPlaceOnCircle.Add(Character, Point);
    CriticalSection.Unlock();
}

bool ARTeam::AssignSuitablePointOnCircleToAI(ARAICharacter* Character)
{
    FVector Result;
    const auto Found = GetSuitablePointOnCircle(Result, Character);

    if (Found)
    {
        AssignPointToAI(Result, Character);
    }
    return Found;
}


ARAICharacter* ARTeam::GetHoldedObjectCharacter() const
{
    if (!PickableItem)
    {
        return nullptr;
    }

    return Cast<ARAICharacter>(PickableItem->GetGrabbingActor());
}

void ARTeam::BuildCircleAroundCharacter()
{
    ClearCircleAroundCharacter();
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
       // ClearCircleAroundCharacter();
    }
}
