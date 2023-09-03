// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RPawnStandsInCircleDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URPawnStandsInCircleDecorator : public UBTDecorator
{
    GENERATED_BODY()
    URPawnStandsInCircleDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bStandsInCircle = true;
};
