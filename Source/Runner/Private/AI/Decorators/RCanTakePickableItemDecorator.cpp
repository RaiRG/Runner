// Runner Game, All Rights Reserved.


#include "AI/Decorators/RCanTakePickableItemDecorator.h"

#include "RPickableItem.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRCanTakePickableItemDecorator, All, All);


URCanTakePickableItemDecorator::URCanTakePickableItemDecorator()
{
	NodeName = "Can Take Pickable Item";
}

bool URCanTakePickableItemDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return false;

	const auto PickableItem = Cast<ARPickableItem>(Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName));
	if (!PickableItem) return false;

	return PickableItem->GetCurrentState() == ERPickableItemState::OnTheFloor;
}
