// Runner Game, All Rights Reserved.


#include "AI/Decorators/RSomeoneMovingToCircleDecorator.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RTeam.h"

URSomeoneMovingToCircleDecorator::URSomeoneMovingToCircleDecorator()
{
    NodeName = "Is Anyone Moving To Circle";
}

bool URSomeoneMovingToCircleDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard)
    {
        return false;
    }

    auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
    if (!Pawn)
    {
        return false;
    }

    auto Team = Pawn->GetTeam();
    if (!Team)
    {
        return false;
    }

    return !Team->IsEveryoneInCircle();
}
