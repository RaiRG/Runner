// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RRunToCircleDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URRunToCircleDecorator : public UBTDecorator
{
	GENERATED_BODY()
	URRunToCircleDecorator();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PickableItemKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlayerCharacterKey;
};
