// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RTeam.h"
#include "GameFramework/GameModeBase.h"
#include "RGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class RUNNER_API ARGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

protected:
    // UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    // int32 NumberOfBots = 10;
    //
    // UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    // TSubclassOf<ARTeam> BotsTeamClass = ARTeam::StaticClass();

    virtual void BeginPlay() override;
};
