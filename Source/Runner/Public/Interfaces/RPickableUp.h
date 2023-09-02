// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPickableUp.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URPickableUp : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUNNER_API IRPickableUp
{
	GENERATED_BODY()

public:
	virtual bool GetIsPickedUp() const =0;
	virtual bool PickUp(AActor* ActorForGrabbing, UMeshComponent* MeshForAttaching = nullptr) = 0;
	virtual void Drop() = 0;
};
