// Runner Game, All Rights Reserved.


#include "UI/RGameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    RestartButton->OnClicked.AddDynamic(this, &URGameOverWidget::OnRestartGame);
}

void URGameOverWidget::OnRestartGame()
{
    const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
