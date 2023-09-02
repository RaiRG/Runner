// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RCoreTypes.h"
#include "RPickableUp.h"
#include "GameFramework/Actor.h"
#include "RPickableItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class RUNNER_API ARPickableItem : public AActor, public IRPickableUp
{
	GENERATED_BODY()

public:
	ARPickableItem();

	virtual bool GetIsPickedUp() const override { return bIsPickedUp; }
	virtual bool PickUp(AActor* ActorForGrabbing, UMeshComponent* MeshForAttaching = nullptr) override;
	virtual void Drop() override;
	ERPickableItemState GetCurrentState() const { return CurrentState; }

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	USphereComponent* InteractionZoneCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PickableUp")
	FName SocketForAttaching = "PickupSocket";

private:
	bool bIsPickedUp;

	ERPickableItemState CurrentState = ERPickableItemState::OnTheFloor;
	void ChangeCurrentState(ERPickableItemState NewState);
};
