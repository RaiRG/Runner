// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API ARGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
