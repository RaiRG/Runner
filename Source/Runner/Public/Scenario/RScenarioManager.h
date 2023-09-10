
// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RScenarioManager.generated.h"

UCLASS()
class RUNNER_API ARScenarioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ARScenarioManager();

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
