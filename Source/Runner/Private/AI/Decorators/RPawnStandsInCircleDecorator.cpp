// Runner Game, All Rights Reserved.


#include "RPawnStandsInCircleDecorator.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

URPawnStandsInCircleDecorator::URPawnStandsInCircleDecorator()
{
    NodeName = "Pawn Stands In Circle";
}

bool URPawnStandsInCircleDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

    return Pawn->GetStandsInCircle() == bStandsInCircle;
}
