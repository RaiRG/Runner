// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RTakePickableItemTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URTakePickableItemTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	URTakePickableItemTask();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PickableItemKey;
};
