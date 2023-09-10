// Runner Game, All Rights Reserved.


#include "AI/RAIController.h"

#include "RAICharacter.h"
#include "Navigation/CrowdFollowingComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogRAIController, All, All);


ARAIController::ARAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
UE_LOG(LogRAIController, Display, TEXT("ARAIController constructor"))
}

void ARAIController::BeginPlay()
{
    Super::BeginPlay();

    auto AICharacter = Cast<ARAICharacter>(GetPawn());
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}
