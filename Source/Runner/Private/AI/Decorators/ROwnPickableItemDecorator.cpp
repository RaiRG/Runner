// Runner Game, All Rights Reserved.


#include "AI/Decorators/ROwnPickableItemDecorator.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UROwnPickableItemDecorator::UROwnPickableItemDecorator()
{
    NodeName = "Does Own Pickable Item";
}

bool UROwnPickableItemDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return false;
    }

    auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
    if (!Pawn)
    {
        return false;
    }

    const auto PickableItem = Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName);
    if (!PickableItem)
    {
        return false;
    }

    return Pawn->DoesHoldObject() && Pawn->GetHoldedObject().GetObject() == PickableItem;
}
