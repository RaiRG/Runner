// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RCoreTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RChangePlayerCharacterMovement.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URChangePlayerCharacterMovement : public UBTTaskNode
{
    GENERATED_BODY()

    URChangePlayerCharacterMovement();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerCharacterKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    ERPlayerCharacterState MovementState;

};
