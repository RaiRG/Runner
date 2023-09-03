// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RBaseCharacter.generated.h"

class UCameraComponent;
class IRPickableUp;
UCLASS()
class RUNNER_API ARBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ARBaseCharacter();

    bool HoldObject(AActor* ActorForHolding);
    void DropHoldedActor();
    bool DoesHoldObject() const { return bHoldSomething; }
    TScriptInterface<IRPickableUp> GetHoldedObject() const { return HoldedObject; }

protected:
    bool bHoldSomething;

    UPROPERTY()
    TScriptInterface<IRPickableUp> HoldedObject;
};
