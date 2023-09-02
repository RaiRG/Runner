// Runner Game, All Rights Reserved.


#include "RPickableItem.h"


#include "RAICharacter.h"
#include "RPlayerCharacter.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRPickableItem, All, All);

ARPickableItem::ARPickableItem()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	InteractionZoneCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	InteractionZoneCollision->SetupAttachment(GetRootComponent());
	InteractionZoneCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

bool ARPickableItem::PickUp(AActor* ActorForGrabbing, UMeshComponent* MeshForAttaching)
{
	if (!MeshForAttaching)
	{
		MeshForAttaching = ActorForGrabbing->FindComponentByClass<UMeshComponent>();
	}
	if (!MeshForAttaching) return false;
	StaticMeshComponent->SetSimulatePhysics(false);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	const auto WasAttached = StaticMeshComponent->AttachToComponent(MeshForAttaching, AttachmentRules,
	                                                                SocketForAttaching);

	if (!WasAttached) return false;
	UE_LOG(LogRPickableItem, Display, TEXT("Pickup!"));
	bIsPickedUp = true;

	if (Cast<ARPlayerCharacter>(ActorForGrabbing))
	{
		ChangeCurrentState(ERPickableItemState::OwnedByPlayer);
	}
	else if (Cast<ARAICharacter>(ActorForGrabbing))
	{
		ChangeCurrentState(ERPickableItemState::OwnedByBot);
	}
	return true;
}

void ARPickableItem::Drop()
{
	const FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false);
	DetachFromActor(Rules);
	StaticMeshComponent->SetSimulatePhysics(true);
	bIsPickedUp = false;
}

void ARPickableItem::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetSimulatePhysics(true);
}

void ARPickableItem::ChangeCurrentState(ERPickableItemState NewState)
{
	CurrentState = NewState;
}
