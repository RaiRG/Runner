// Runner Game, All Rights Reserved.


#include "AI/Services/RCheckPickableItemState.h"

#include "RPickableItem.h"
#include "BehaviorTree/BlackboardComponent.h"

URCheckPickableItemState::URCheckPickableItemState()
{
}

void URCheckPickableItemState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }
    const auto PickableItem = Cast<ARPickableItem>(Blackboard->GetValueAsObject(PickableItemKey.SelectedKeyName));
    if (!PickableItem)
    {
        return Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }

    Blackboard->SetValueAsEnum(PickableItemStateKey.SelectedKeyName, static_cast<uint8>(PickableItem->GetCurrentState()));
}
