// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RReportStateRegardingCircleTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URReportStateRegardingCircleTask : public UBTTaskNode
{
    GENERATED_BODY()

    URReportStateRegardingCircleTask();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector CircleLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bInCircle = true;
};
