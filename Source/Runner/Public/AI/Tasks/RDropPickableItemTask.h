// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RDropPickableItemTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URDropPickableItemTask : public UBTTaskNode
{
	GENERATED_BODY()

	URDropPickableItemTask();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector PickableItemKey;
};
