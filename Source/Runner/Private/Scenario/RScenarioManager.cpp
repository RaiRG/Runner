// Runner Game, All Rights Reserved.


#include "Scenario/RScenarioManager.h"

#include "RGameModeBase.h"
#include "RPlayerCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogRScenarioManager, All, All);


ARScenarioManager::ARScenarioManager()
{
    PrimaryActorTick.bCanEverTick = true;

}

void ARScenarioManager::NotifyActorBeginOverlap(AActor* OtherActor)
{
    UE_LOG(LogRScenarioManager, Display, TEXT("ActorBeginOverlap"));
    Super::NotifyActorBeginOverlap(OtherActor);

    if (!GetWorld()) return;
    if (!Cast<ARPlayerCharacter>(OtherActor)) return;

    auto GameMode = Cast<ARGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    GameMode->GameOver();
}
