// Runner Game, All Rights Reserved.


#include "AI/Tasks/RDropPickableItemTask.h"

#include "AIController.h"
#include "RAICharacter.h"

URDropPickableItemTask::URDropPickableItemTask()
{
	NodeName = "Drop Pickable Item";
}

EBTNodeResult::Type URDropPickableItemTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	Pawn->DropHoldedActor();
	return EBTNodeResult::Succeeded;
}
