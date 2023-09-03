// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RFindLocationOnCircleTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URFindLocationOnCircleTask : public UBTTaskNode
{
    GENERATED_BODY()

    URFindLocationOnCircleTask();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector CircleLocationKey;
};
