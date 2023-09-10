// Runner Game, All Rights Reserved.


#include "Player/RGamePlayerController.h"

#include "RGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogRGamePlayerController, All, All);


void ARGamePlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = false;
    if (GetWorld())
    {
        if (const auto GameMode = Cast<ARGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddDynamic(this, &ARGamePlayerController::OnMatchStateChanged);
        }
    }
}

void ARGamePlayerController::OnMatchStateChanged(ERMatchState State)
{
    UE_LOG(LogRGamePlayerController, Display, TEXT("OnMatchStateChanged"))
    if (State == ERMatchState::InProgress)
    {
        UE_LOG(LogRGamePlayerController, Display, TEXT("FInputModeGameOnly"))
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        UE_LOG(LogRGamePlayerController, Display, TEXT("FInputModeUIOnly"))
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}
