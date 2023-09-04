// Runner Game, All Rights Reserved.


#include "RPickableItem.h"


#include "RAICharacter.h"
#include "RGameModeBase.h"
#include "RPlayerCharacter.h"
#include "RTeam.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogRPickableItem, All, All);

ARPickableItem::ARPickableItem()
{
    PrimaryActorTick.bCanEverTick = true;
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    SetRootComponent(StaticMeshComponent);

    InteractionZoneCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    InteractionZoneCollision->SetupAttachment(GetRootComponent());
    InteractionZoneCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
}

bool ARPickableItem::PickUp(AActor* ActorForGrabbing, UMeshComponent* MeshForAttaching)
{
    if (!MeshForAttaching)
    {
        MeshForAttaching = ActorForGrabbing->FindComponentByClass<UMeshComponent>();
    }
    if (!MeshForAttaching)
    {
        return false;
    }

    StaticMeshComponent->SetSimulatePhysics(false);
    const FAttachmentTransformRules AttachmentRule = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
    const auto WasAttached = StaticMeshComponent->AttachToComponent(MeshForAttaching, AttachmentRule,
        SocketForAttaching);
    if (!WasAttached)
    {
        return false;
    }

    bIsPickedUp = true;
    GrabbingActor = ActorForGrabbing;
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

void ARPickableItem::Drop(FVector Impulse)
{
    const FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false);
    DetachFromActor(Rules);
    StaticMeshComponent->SetSimulatePhysics(true);
    StaticMeshComponent->AddImpulse(Impulse, NAME_None, true);
    bIsPickedUp = false;
    GrabbingActor = nullptr;
    SetStateAccordingToCircle();
}


void ARPickableItem::BeginPlay()
{
    Super::BeginPlay();
    StaticMeshComponent->SetSimulatePhysics(true);
    BotsTeam = Cast<ARTeam>(UGameplayStatics::GetActorOfClass(GetWorld(), ARTeam::StaticClass()));
    if (BotsTeam)
    {
        SetStateAccordingToCircle();
    }
}

void ARPickableItem::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (CurrentState == ERPickableItemState::InsideCircle || CurrentState == ERPickableItemState::OutsideCircle)
    {
        if (BotsTeam)
        {
            SetStateAccordingToCircle();
        }
    }
}

void ARPickableItem::ChangeCurrentState(ERPickableItemState NewState)
{
    if (CurrentState == NewState)
    {
        return;
    }
    CurrentState = NewState;
    PickableUpActorChangeState.Broadcast(CurrentState);
    UE_LOG(LogRPickableItem, Display, TEXT("New state %s"), *UEnum::GetValueAsString(CurrentState))
}

void ARPickableItem::SetStateAccordingToCircle()
{
    if (!BotsTeam)
    {
        return;
    }
    const auto NewState = BotsTeam->IsPointInsideCircle(StaticMeshComponent->GetComponentLocation())
                              ? ERPickableItemState::InsideCircle
                              : ERPickableItemState::OutsideCircle;
    ChangeCurrentState(NewState);
}
