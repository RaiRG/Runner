// Runner Game, All Rights Reserved.


#include "AI/Tasks/RChangePlayerCharacterMovement.h"

#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRChangePlayerCharacterMovement, All, All);

URChangePlayerCharacterMovement::URChangePlayerCharacterMovement()
{
    NodeName = "Change Player Character Movement State";
}

EBTNodeResult::Type URChangePlayerCharacterMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return EBTNodeResult::Failed;
    }

    const auto PlayerCharacter = Cast<ARPlayerCharacter>(
        Blackboard->GetValueAsObject(PlayerCharacterKey.SelectedKeyName));
    if (!PlayerCharacter)
    {
        return EBTNodeResult::Failed;
    }

    if (bEnableMovement)
    {
        UE_LOG(LogRChangePlayerCharacterMovement, Display, TEXT("UnBlockMovement of character!"));
        PlayerCharacter->UnblockMovement();
    }
    else
    {
        UE_LOG(LogRChangePlayerCharacterMovement, Display, TEXT("BlockMovement of character!"));
        PlayerCharacter->BlockMovement();
    }
    return EBTNodeResult::Succeeded;
}
