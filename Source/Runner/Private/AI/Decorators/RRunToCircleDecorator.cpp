// Runner Game, All Rights Reserved.


#include "AI/Decorators/RRunToCircleDecorator.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RCoreTypes.h"
#include "RPickableItem.h"
#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

URRunToCircleDecorator::URRunToCircleDecorator()
{
	NodeName = "Can Run To Circle Decorator";
}

bool URRunToCircleDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return false;

	const auto PickableItem = Cast<ARPickableItem>(Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName));
	if (!PickableItem) return false;

	const auto PlayerCharacter = Cast<ARPlayerCharacter>(
		Blackboard->GetValueAsObject(PlayerCharacterKey.SelectedKeyName));
	if (!PlayerCharacter) return false;

	auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
	if (!Pawn) return false;
	//пользователь заблокирован, но какой-то бот держит в руках предмет и павн еще не в кругу
	return !PlayerCharacter->GetCanMove() && PickableItem->GetCurrentState() == ERPickableItemState::OwnedByBot && !Pawn->GetStandsInCircle();
}
