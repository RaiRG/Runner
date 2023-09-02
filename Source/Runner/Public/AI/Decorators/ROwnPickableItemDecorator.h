// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ROwnPickableItemDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API UROwnPickableItemDecorator : public UBTDecorator
{
	GENERATED_BODY()
	UROwnPickableItemDecorator();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PickableItemKey;
};
