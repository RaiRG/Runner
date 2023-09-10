// Runner Game, All Rights Reserved.


#include "RPlayerCharacter.h"

#include "RPickableUp.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogRPlayerCharacter, All, All);

ARPlayerCharacter::ARPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetRootComponent());
    CameraComponent->bUsePawnControlRotation = true;
}

void ARPlayerCharacter::BlockMovement()
{
    ChangeMovementState(ERPlayerCharacterState::MovementBlocked);
}

void ARPlayerCharacter::UnblockMovement()
{
    ChangeMovementState(ERPlayerCharacterState::MovementUnblocked);
}


void ARPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ARPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ARPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ARPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ARPlayerCharacter::TryToPickUpOverlappedActor);
    PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &ARPlayerCharacter::DropHoldedActorInFront);
}

void ARPlayerCharacter::DropHoldedActorInFront()
{
    auto ImpulseDirection = GetActorForwardVector();
    ImpulseDirection.Normalize();
    const auto Impulse = ImpulseDirection * DropImpulseStrength;
    Super::DropHoldedActor(Impulse);
}

void ARPlayerCharacter::TryToPickUpOverlappedActor()
{
    if (bHoldSomething)
    {
        return;
    }
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AActor::StaticClass());
    for (auto OverlappingActor : OverlappingActors)
    {
        if (UKismetSystemLibrary::DoesImplementInterface(OverlappingActor, URPickableUp::StaticClass()))
        {
            const auto Hold = HoldObject(OverlappingActor);
            if (Hold)
            {
                break;
            }
        }
    }
}


void ARPlayerCharacter::MoveForward(float Amount)
{
    if (MovementState==ERPlayerCharacterState::MovementBlocked)
    {
        return;
    }
    if (Amount == 0.0f)
    {
        return;
    }
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ARPlayerCharacter::MoveRight(float Amount)
{
    if (MovementState==ERPlayerCharacterState::MovementBlocked)
    {
        return;
    }
    if (Amount == 0.0f)
    {
        return;
    }
    AddMovementInput(GetActorRightVector(), Amount);
}

void ARPlayerCharacter::ChangeMovementState(ERPlayerCharacterState NewState)
{
    if (MovementState == NewState)
    {
        return;
    }
    MovementState = NewState;
    PlayerCharacterChangeMovementState.Broadcast(MovementState);
    UE_LOG(LogRPlayerCharacter, Display, TEXT("ChangeMovementState to %s"), *UEnum::GetValueAsString(MovementState));
}
