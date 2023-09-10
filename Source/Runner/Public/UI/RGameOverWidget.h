// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RGameOverWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class RUNNER_API URGameOverWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta=(BindWidget))
    UButton* RestartButton;

private:
    UFUNCTION()
    void OnRestartGame();
};
