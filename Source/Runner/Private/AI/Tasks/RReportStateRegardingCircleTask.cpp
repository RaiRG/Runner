// Runner Game, All Rights Reserved.


#include "AI/Tasks/RReportStateRegardingCircleTask.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRStopMovingToCircleTask, All, All);


URReportStateRegardingCircleTask::URReportStateRegardingCircleTask()
{
    NodeName = "Say About State Regarding Circle";
}

EBTNodeResult::Type URReportStateRegardingCircleTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (!Controller || !Blackboard) { return EBTNodeResult::Failed; }

    auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }
    if (bInCircle)
    {
        UE_LOG(LogRStopMovingToCircleTask, Display, TEXT("%s in Circle, Controller %s"), *Pawn->GetName(),
            *Pawn->GetController()->GetName());
        Pawn->SetStandsInCircle(true);
    }
    else
    {
        Pawn->SetStandsInCircle(false);
        Blackboard->ClearValue(CircleLocationKey.SelectedKeyName);
    }
    return EBTNodeResult::Succeeded;
}
