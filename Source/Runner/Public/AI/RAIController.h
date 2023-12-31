// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "RAIController.generated.h"

class UCrowdFollowingComponent;
/**
 * 
 */
UCLASS()
class RUNNER_API ARAIController : public AAIController
{
    GENERATED_BODY()

    ARAIController();
    ARAIController(const FObjectInitializer& ObjectInitializer);
    
    virtual void BeginPlay() override;
};
