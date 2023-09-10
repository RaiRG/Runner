// Runner Game, All Rights Reserved.


#include "RAICharacter.h"

#include "AIController.h"
#include "RAIController.h"
#include "RPickableItem.h"
#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ARAICharacter::ARAICharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = ARAIController::StaticClass();
    bUseControllerRotationYaw = true;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 100.0f, 0.0f);
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
    }
}


void ARAICharacter::BeginPlay()
{
    Super::BeginPlay();

    // Сохраняем указатель на поднимаемую сферу
    const auto PickableItem = Cast<ARPickableItem>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ARPickableItem::StaticClass()));

    // Сохраняем указатель на персонажа пользователя
    const auto PlayerPawn = Cast<ARPlayerCharacter>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ARPlayerCharacter::StaticClass()));

    if (auto AIController = Cast<AAIController>(GetController()))
    {
        if (auto Blackboard = AIController->GetBlackboardComponent())
        {
            Blackboard->SetValueAsObject(PickableItemKeyName, PickableItem);
            Blackboard->SetValueAsObject(PlayerCharacterKeyName, PlayerPawn);
            Blackboard->SetValueAsVector(PatrolPositionKeyName, GetActorLocation());
        }
    }
}
