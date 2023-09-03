// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RBaseCharacter.h"
#include "RCoreTypes.h"
#include "GameFramework/Character.h"
#include "RPlayerCharacter.generated.h"

class IRPickableUp;
UCLASS()
class RUNNER_API ARPlayerCharacter : public ARBaseCharacter
{
    GENERATED_BODY()

public:
    ARPlayerCharacter();

    void BlockMovement();
    void UnblockMovement();
    ERPlayerCharacterState GetMovementState() const { return MovementState; }
    FOnPlayerCharacterChangeMovementStateSignature PlayerCharacterChangeMovementState;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void ChangeMovementState(ERPlayerCharacterState NewStateCanMove);

    void TryToPickUpOverlappedActor();

    ERPlayerCharacterState MovementState = ERPlayerCharacterState::MovementUnblocked;

};
