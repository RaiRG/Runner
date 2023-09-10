// Runner Game, All Rights Reserved.


#include "UI/RGameHUD.h"

#include "RCoreTypes.h"
#include "RGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ARGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ERMatchState::GameOver, CreateWidget(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ARGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddDynamic(this, &ARGameHUD::OnMatchStateChanged);
        }
    }
}

void ARGameHUD::OnMatchStateChanged(ERMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}
