// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RCanTakePickableItemDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URCanTakePickableItemDecorator : public UBTDecorator
{
	GENERATED_BODY()

	URCanTakePickableItemDecorator();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PickableItemKey;
};
