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
	bool GetCanMove() const { return bCanMove; }
	FOnPlayerCharacterChangeMovementStateSignature PlayerCharacterChangeMovementState;  
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void ChangeMovementState(bool NewState);
	bool bCanMove = true;
};
