// Runner Game, All Rights Reserved.


#include "AI/Tasks/RFindLocationOnCircleTask.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RAITeam.h"
#include "BehaviorTree/BlackboardComponent.h"

URFindLocationOnCircleTask::URFindLocationOnCircleTask()
{
	NodeName = "Get Location On Circle Around Player Character";
}

EBTNodeResult::Type URFindLocationOnCircleTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;
	
	auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	
	auto Team = Pawn->GetTeam();
	if (!Team)  return EBTNodeResult::Failed;

	FVector LocationOnCircle;
	auto FoundLocation = Team->GetLocationOnShape(LocationOnCircle);

	if (!FoundLocation) return EBTNodeResult::Failed;
	
	Blackboard->SetValueAsVector(CircleLocationKey.SelectedKeyName, LocationOnCircle);
	return EBTNodeResult::Succeeded;
}
