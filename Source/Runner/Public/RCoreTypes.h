// Runner Game, All Rights Reserved.

#pragma once
#include "RCoreTypes.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCharacterChangeMovementStateSignature, bool, bCanMove);


UENUM(BlueprintType)
enum class ERPickableItemState : uint8
{
	OnTheFloor,
	OwnedByPlayer,
	OwnedByBot
};