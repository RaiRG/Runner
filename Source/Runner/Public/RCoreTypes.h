// Runner Game, All Rights Reserved.

#pragma once
#include "RCoreTypes.generated.h"


UENUM(BlueprintType)
enum class ERPickableItemState : uint8
{
    OwnedByPlayer,
    OwnedByBot,
    InsideCircle,
    OutsideCircle
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCharacterChangeMovementStateSignature, bool, bCanMove);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickableUpActorChangeStateSignature, ERPickableItemState, NewState);
