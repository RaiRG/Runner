// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API ARGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    UFUNCTION()
    void OnMatchStateChanged(ERMatchState State);
};
