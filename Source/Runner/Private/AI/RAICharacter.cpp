// Runner Game, All Rights Reserved.


#include "RAICharacter.h"

#include "AIController.h"
#include "RAIController.h"
#include "RPickableItem.h"
#include "RPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogRAICharacter, All, All);


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


bool ARAICharacter::HoldObject(AActor* ActorForHolding)
{
    const auto Attached = Super::HoldObject(ActorForHolding);
    
    if (Attached)
    {
        UE_LOG(LogRAICharacter, Display, TEXT("SetActorEnableCollision false"));

        ActorForHolding->SetActorEnableCollision(false);
    }
    return Attached;
}

void ARAICharacter::DropHoldedActor(FVector Impulse)
{
    auto HoldedActor = Cast<AActor>(HoldedObject.GetObject());
    UE_LOG(LogRAICharacter, Display, TEXT("DropHoldedActor"));

    if (HoldedActor)
    {
        UE_LOG(LogRAICharacter, Display, TEXT("SetActorEnableCollision true"));
        HoldedActor->SetActorEnableCollision(true);
    }
    Super::DropHoldedActor(Impulse);
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
