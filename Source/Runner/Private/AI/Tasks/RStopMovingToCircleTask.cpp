// Runner Game, All Rights Reserved.


#include "AI/Tasks/RStopMovingToCircleTask.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRStopMovingToCircleTask, All, All);


URStopMovingToCircleTask::URStopMovingToCircleTask()
{
	NodeName = "Stop Moving To Circle Point";
}

EBTNodeResult::Type URStopMovingToCircleTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Controller || !Blackboard) { return EBTNodeResult::Failed; }

	auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;
	Pawn->SetStandsInCircle(true);

	UE_LOG(LogRStopMovingToCircleTask, Display, TEXT("StopMovingToCircleTask on %s"), *Pawn->GetName())
	Blackboard->ClearValue(CircleLocationKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}
