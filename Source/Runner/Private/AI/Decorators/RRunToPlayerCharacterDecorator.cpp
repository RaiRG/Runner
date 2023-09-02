// Runner Game, All Rights Reserved.


#include "AI/Decorators/RRunToPlayerCharacterDecorator.h"

#include "RPickableItem.h"
#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRunToPlayerCharacterDecorator, All, All);

URRunToPlayerCharacterDecorator::URRunToPlayerCharacterDecorator()
{
	NodeName = "Can Run To Player Character";
}

bool URRunToPlayerCharacterDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                 uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return false;

	const auto PickableItem = Cast<ARPickableItem>(Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName));
	if (!PickableItem) return false;
	
	const auto PlayerCharacter = Cast<ARPlayerCharacter>(
		Blackboard->GetValueAsObject(PlayerCharacterKey.SelectedKeyName));
	if (!PlayerCharacter) return false;

	return PlayerCharacter->GetCanMove() && PickableItem->GetCurrentState() == ERPickableItemState::OwnedByBot;
}
