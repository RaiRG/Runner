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
    ChangeMovementState(false);
}

void ARPlayerCharacter::UnblockMovement()
{
    ChangeMovementState(true);
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
    PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &ARPlayerCharacter::DropHoldedActor);
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
    if (!bCanMove)
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
    if (!bCanMove)
    {
        return;
    }
    if (Amount == 0.0f)
    {
        return;
    }
    AddMovementInput(GetActorRightVector(), Amount);
}

void ARPlayerCharacter::ChangeMovementState(bool NewStateCanMove)
{
    if (bCanMove == NewStateCanMove)
    {
        return;
    }
    bCanMove = NewStateCanMove;
    PlayerCharacterChangeMovementState.Broadcast(bCanMove);
    UE_LOG(LogRPlayerCharacter, Display, TEXT("ChangeMovementState to %i"), bCanMove);
}
