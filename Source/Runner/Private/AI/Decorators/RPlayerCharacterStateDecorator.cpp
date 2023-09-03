// Runner Game, All Rights Reserved.


#include "AI/Decorators/RPlayerCharacterStateDecorator.h"

#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRunToPlayerCharacterDecorator, All, All);

URPlayerCharacterStateDecorator::URPlayerCharacterStateDecorator()
{
    NodeName = "Check Player Character And Pickable Item State";
}

bool URPlayerCharacterStateDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return false;
    }

    const auto PlayerCharacter = Cast<ARPlayerCharacter>(
        Blackboard->GetValueAsObject(PlayerCharacterKey.SelectedKeyName));
    if (!PlayerCharacter)
    {
        return false;
    }

    return PlayerCharacter->GetCanMove() == bCanPlayerCharacterMove;
}
