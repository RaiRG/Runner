// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RSetFocusTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URSetFocusTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URSetFocusTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	FBlackboardKeySelector TargetActor;
	
};
