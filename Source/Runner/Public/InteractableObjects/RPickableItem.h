// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RCoreTypes.h"
#include "RPickableUp.h"
#include "GameFramework/Actor.h"
#include "RPickableItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class ARTeam;

UCLASS()
class RUNNER_API ARPickableItem : public AActor, public IRPickableUp
{
    GENERATED_BODY()

public:
    ARPickableItem();

    virtual bool GetIsPickedUp() const override { return bIsPickedUp; }
    virtual bool PickUp(AActor* ActorForGrabbing, UMeshComponent* MeshForAttaching = nullptr) override;
    virtual void Drop(FVector Impulse = FVector()) override;
    virtual AActor* GetGrabbingActor() const override { return GrabbingActor; };
    UFUNCTION(BlueprintCallable, BlueprintPure)
    ERPickableItemState GetCurrentState() const { return CurrentState; }

    FOnPickableUpActorChangeStateSignature PickableUpActorChangeState;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
    USphereComponent* InteractionZoneCollision;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PickableUp")
    FName SocketForAttaching = "PickupSocket";

private:
    bool bIsPickedUp;
    UPROPERTY()
    AActor* GrabbingActor;
    ERPickableItemState CurrentState;
    void SetStateAccordingToCircle();
    void ChangeCurrentState(ERPickableItemState NewState);

    UPROPERTY()
    ARTeam* BotsTeam;
};
