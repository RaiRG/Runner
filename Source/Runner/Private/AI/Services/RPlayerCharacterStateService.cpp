// Runner Game, All Rights Reserved.


#include "AI/Services/RPlayerCharacterStateService.h"

#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void URPlayerCharacterStateService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }
    const auto PlayerCharacter = Cast<ARPlayerCharacter>(Blackboard->GetValueAsObject(PlayerCharacterKey.SelectedKeyName));
    if (!PlayerCharacter)
    {
        return Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }

    Blackboard->SetValueAsEnum(PlayerCharacterMovementStateKey.SelectedKeyName, static_cast<uint8>(PlayerCharacter->GetMovementState()));
}
