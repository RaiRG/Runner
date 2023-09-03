// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RPlayerCharacterStateDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URPlayerCharacterStateDecorator : public UBTDecorator
{
    GENERATED_BODY()

    URPlayerCharacterStateDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerCharacterKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bCanPlayerCharacterMove = true;

};
