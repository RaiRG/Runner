// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RSomeoneMovingToCircleDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URSomeoneMovingToCircleDecorator : public UBTDecorator
{
	GENERATED_BODY()

	URSomeoneMovingToCircleDecorator();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
