// Runner Game, All Rights Reserved.


#include "AI/Services/RLocationOnCircle.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RTeam.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogLocationOnCircle, All, All);

void URLocationOnCircle::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }

    auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
    if (!Pawn)
    {
        return;
    }

    auto Team = Pawn->GetTeam();
    if (!Team)
    {
        return;
    }

    FVector LocationOnCircle;
    const auto FoundLocation = Team->GetLocationOnCircle(LocationOnCircle, Pawn);
    if (!FoundLocation)
    {
        Blackboard->ClearValue(CircleLocationKey.SelectedKeyName);
        return;
    }

    bool PathExist = Team->IsPointReachableByCharacter(LocationOnCircle, Pawn);
    if (!PathExist)
    {
        UE_LOG(LogLocationOnCircle, Error, TEXT("Path doesn't exist, but Location still assigned"));
    }
    Blackboard->SetValueAsVector(CircleLocationKey.SelectedKeyName, LocationOnCircle);
}
