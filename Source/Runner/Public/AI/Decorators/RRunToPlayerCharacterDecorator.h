// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RRunToPlayerCharacterDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URRunToPlayerCharacterDecorator : public UBTDecorator
{
	GENERATED_BODY()

	URRunToPlayerCharacterDecorator();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PickableItemKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PlayerCharacterKey;
};
