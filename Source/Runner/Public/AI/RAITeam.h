// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "RAITeam.generated.h"

class ARAICharacter;
UCLASS()
class RUNNER_API ARAITeam : public AActor
{
	GENERATED_BODY()

public:
	ARAITeam();

	void AddMember(ARAICharacter* NewMember);
	bool GetLocationOnShape(FVector& Result);
	bool DoesEveryoneInCircle() const;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerCharacterChangeMovementState(bool bCanMove);

	void OnFindAllPossiblePoints(TSharedPtr<FEnvQueryResult> Result);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UEnvQuery* EnvQueryForBotsStandingShape;

private:
	UPROPERTY()
	TArray<ARAICharacter*> AllMembers;

	UPROPERTY()
	TArray<FVector> AllPossiblePointsForStandingMembers;

	FCriticalSection CriticalSection;
};
