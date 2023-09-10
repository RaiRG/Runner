// Runner Game, All Rights Reserved.


#include "RGameModeBase.h"

#include "EngineUtils.h"
DEFINE_LOG_CATEGORY_STATIC(LogRGameModeBase, All, All);

void ARGameModeBase::GameOver()
{
    SetPause(GetWorld()->GetFirstPlayerController());
    SetMatchState(ERMatchState::GameOver);
}

void ARGameModeBase::BeginPlay()
{
    UE_LOG(LogRGameModeBase, Display, TEXT("BeginPlay!"));
    Super::BeginPlay();
    SetMatchState(ERMatchState::InProgress);
}

void ARGameModeBase::SetMatchState(ERMatchState NewState)
{
    if (NewState == MatchState) return;
    MatchState = NewState;
    OnMatchStateChanged.Broadcast(MatchState);
}
