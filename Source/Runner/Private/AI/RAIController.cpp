// Runner Game, All Rights Reserved.


#include "AI/RAIController.h"

#include "RAICharacter.h"

void ARAIController::BeginPlay()
{
    Super::BeginPlay();

    auto AICharacter = Cast<ARAICharacter>(GetPawn());
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}
