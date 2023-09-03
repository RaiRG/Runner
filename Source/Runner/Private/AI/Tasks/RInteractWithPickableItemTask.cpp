// Runner Game, All Rights Reserved.


#include "AI/Tasks/RInteractWithPickableItemTask.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RPickableItem.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRInteractWithPickableItemTask, All, All);


URInteractWithPickableItemTask::URInteractWithPickableItemTask()
{
    NodeName = "InteractWithPickableItem";
}

EBTNodeResult::Type URInteractWithPickableItemTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return EBTNodeResult::Failed;
    }

    const auto PickableItem = Cast<ARPickableItem>(Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName));
    if (!PickableItem)
    {
        return EBTNodeResult::Failed;
    }

    auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    bool SuccessfulInteraction = true;
    if (bTake)
    {
        UE_LOG(LogRInteractWithPickableItemTask, Display, TEXT("Hold!"))
        SuccessfulInteraction = Pawn->HoldObject(PickableItem);
    }
    else
    {
        UE_LOG(LogRInteractWithPickableItemTask, Display, TEXT("Drop!"))
        Pawn->DropHoldedActor();
    }
    return SuccessfulInteraction ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
