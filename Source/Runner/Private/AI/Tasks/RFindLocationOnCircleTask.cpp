// Runner Game, All Rights Reserved.


#include "AI/Tasks/RFindLocationOnCircleTask.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RTeam.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRFindLocationOnCircleTask, All, All);


URFindLocationOnCircleTask::URFindLocationOnCircleTask()
{
    NodeName = "Get Location On Circle Around Player Character";
}

EBTNodeResult::Type URFindLocationOnCircleTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return EBTNodeResult::Failed;
    }

    auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    auto Team = Pawn->GetTeam();
    if (!Team)
    {
        return EBTNodeResult::Failed;
    }

    FVector LocationOnCircle;
    const auto FoundLocation = Team->TakeLocationOnCircle(LocationOnCircle, Pawn);
    if (!FoundLocation)
    {
        return EBTNodeResult::Failed;
    }

    UE_LOG(LogRFindLocationOnCircleTask, Display, TEXT("LocationOnCircle for %s is %s"), *OwnerComp.GetAIOwner()->GetName(),
        *LocationOnCircle.ToString())
    Blackboard->SetValueAsVector(CircleLocationKey.SelectedKeyName, LocationOnCircle);
    return EBTNodeResult::Succeeded;
}
