// Runner Game, All Rights Reserved.


#include "AI/Tasks/RSetFocusTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

URSetFocusTask::URSetFocusTask()
{
    NodeName = "Set Focus";
}

EBTNodeResult::Type URSetFocusTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (!Controller || !Blackboard) { return EBTNodeResult::Failed; }
    
    const auto FocusActor = Cast<AActor>(Blackboard->GetValueAsObject(TargetActor.SelectedKeyName));

    if (!FocusActor)
    {
        return EBTNodeResult::Failed;
    }

    if (bEnableFocus)
    {
        auto CurrentPawn = Controller->GetPawn();
        if (CurrentPawn)
        {
            auto LookAtFocusActorRotation = UKismetMathLibrary::FindLookAtRotation(CurrentPawn->GetActorLocation(), FocusActor->GetActorLocation());
            CurrentPawn->SetActorRotation(LookAtFocusActorRotation);
    
        }
        Controller->SetFocus(FocusActor);
    }
    else
    {
        Controller->ClearFocus(EAIFocusPriority::Gameplay);
    }

    return EBTNodeResult::Succeeded;
}
