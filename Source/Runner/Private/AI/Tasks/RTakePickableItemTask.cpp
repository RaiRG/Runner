// Runner Game, All Rights Reserved.


#include "AI/Tasks/RTakePickableItemTask.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RPickableItem.h"
#include "BehaviorTree/BlackboardComponent.h"

URTakePickableItemTask::URTakePickableItemTask()
{
	NodeName = "Take Pickable Item";

}

EBTNodeResult::Type URTakePickableItemTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto PickableItem = Cast<ARPickableItem>(Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName));
	if (!PickableItem || PickableItem->GetIsPickedUp()) return EBTNodeResult::Failed;
	
	auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	const auto ItemWasPickedUp = Pawn->HoldObject(PickableItem);
	return ItemWasPickedUp ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	
}
