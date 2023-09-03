// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RPlayerCharacterStateService.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URPlayerCharacterStateService : public UBTService
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerCharacterKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PlayerCharacterMovementStateKey;

    
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
