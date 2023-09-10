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

public:
    void GameOver();
    FOnMatchStateChangedSignature OnMatchStateChanged;

protected:
    virtual void BeginPlay() override;
private:
    ERMatchState MatchState;
    void SetMatchState(ERMatchState NewState);
};
