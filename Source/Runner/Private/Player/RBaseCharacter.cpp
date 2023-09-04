// Runner Game, All Rights Reserved.


#include "Player/RBaseCharacter.h"

#include "Interfaces/RPickableUp.h"

DEFINE_LOG_CATEGORY_STATIC(LogRBaseCharacter, All, All);

ARBaseCharacter::ARBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARBaseCharacter::DropHoldedActor(FVector Impulse)
{
    if (!bHoldSomething)
    {
        return;
    }
    MoveIgnoreActorRemove(Cast<AActor>(HoldedObject.GetObject()));
    HoldedObject->Drop(Impulse);
    HoldedObject = nullptr;
    bHoldSomething = false;
}

bool ARBaseCharacter::HoldObject(AActor* ActorForHolding)
{
    HoldedObject = TScriptInterface<IRPickableUp>(ActorForHolding);
    if (HoldedObject && !HoldedObject->GetIsPickedUp())
    {
        const auto WasHolded = HoldedObject->PickUp(this, GetMesh());
        if (WasHolded)
        {
            UE_LOG(LogRBaseCharacter, Display, TEXT("Pickup!"));
            MoveIgnoreActorAdd(ActorForHolding);
            bHoldSomething = true;
            return true;
        }
    }
    return false;
}
