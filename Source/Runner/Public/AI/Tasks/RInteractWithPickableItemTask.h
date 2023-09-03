// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RInteractWithPickableItemTask.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URInteractWithPickableItemTask : public UBTTaskNode
{
    GENERATED_BODY()
    URInteractWithPickableItemTask();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PickableItemKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(ToolTip="True if eed take, false if need drop"))
    bool bTake = true;
};
