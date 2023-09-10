// Runner Game, All Rights Reserved.

#pragma once
#include "RCoreTypes.generated.h"


UENUM(BlueprintType)
enum class ERPickableItemState : uint8
{
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

UENUM(BlueprintType)
enum class ERMatchState : uint8
{
    InProgress,
    GameOver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCharacterChangeMovementStateSignature, ERPlayerCharacterState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickableUpActorChangeStateSignature, ERPickableItemState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ERMatchState, NewState);
