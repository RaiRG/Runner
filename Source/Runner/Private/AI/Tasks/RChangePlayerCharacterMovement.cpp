// Runner Game, All Rights Reserved.


#include "AI/Tasks/RChangePlayerCharacterMovement.h"

#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

URChangePlayerCharacterMovement::URChangePlayerCharacterMovement()
{
	NodeName = "Change Player Character Movement State";
}

EBTNodeResult::Type URChangePlayerCharacterMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto PlayerCharacter = Cast<ARPlayerCharacter>(
		Blackboard->GetValueAsObject(PlayerCharacterKey.SelectedKeyName));
	if (!PlayerCharacter) return EBTNodeResult::Failed;

	if (bEnableMovement)
	{
		PlayerCharacter->UnblockMovement();
	}
	else
	{
		PlayerCharacter->BlockMovement();
	}
	return EBTNodeResult::Succeeded;
}
