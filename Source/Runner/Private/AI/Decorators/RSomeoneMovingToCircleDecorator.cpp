// Runner Game, All Rights Reserved.


#include "AI/Decorators/RSomeoneMovingToCircleDecorator.h"

#include "AIController.h"
#include "RAICharacter.h"
#include "RAITeam.h"

URSomeoneMovingToCircleDecorator::URSomeoneMovingToCircleDecorator()
{
	NodeName = "Is Anyone Moving To Circle";
}

bool URSomeoneMovingToCircleDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                  uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return false;


	const auto Pawn = Cast<ARAICharacter>(Controller->GetPawn());
	if (!Pawn) return false;

	const auto Team = Pawn->GetTeam();
	if (!Team) return false;


	UE_LOG(LogTemp, Display, TEXT("SomeoneMovingToCircleDecorator %s"), !Team->DoesEveryoneInCircle() ? *FString("True") : *FString("False"));
	return !Team->DoesEveryoneInCircle();
}
