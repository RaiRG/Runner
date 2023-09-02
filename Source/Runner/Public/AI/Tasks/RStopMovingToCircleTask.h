// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RStopMovingToCircleTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URStopMovingToCircleTask : public UBTTaskNode
{
	GENERATED_BODY()

	URStopMovingToCircleTask();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CircleLocationKey;
};
