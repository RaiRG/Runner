// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RGameHUD.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class RUNNER_API ARGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ERMatchState, UUserWidget*> GameWidgets;

    UFUNCTION()
    void OnMatchStateChanged(ERMatchState State);


    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;
};
