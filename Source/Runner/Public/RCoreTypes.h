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

UENUM(BlueprintType)
enum class ERPlayerCharacterState : uint8
{
    MovementBlocked,
    MovementUnblocked
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCharacterChangeMovementStateSignature, ERPlayerCharacterState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickableUpActorChangeStateSignature, ERPickableItemState, NewState);
