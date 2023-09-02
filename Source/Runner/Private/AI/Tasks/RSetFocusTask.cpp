// Runner Game, All Rights Reserved.


#include "AI/Tasks/RSetFocusTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	OwnerComp.GetAIOwner()->SetFocus(FocusActor);
	Controller->SetFocus(FocusActor);

	return EBTNodeResult::Succeeded;
}
