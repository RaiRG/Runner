// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RBaseCharacter.h"
#include "RAICharacter.generated.h"


class UBehaviorTree;
class ARAITeam;
UCLASS()
class RUNNER_API ARAICharacter : public ARBaseCharacter
{
	GENERATED_BODY()

public:
	ARAICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	void SetTeam(ARAITeam* NewTeam) { Team = NewTeam; }
	ARAITeam* GetTeam() const { return Team; }

	bool GetStandsInCircle() const {return bStandsInCircle;}
	void SetStandsInCircle(bool Val) {bStandsInCircle = Val; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	FName PickableItemKeyName = "PickableSphere";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	FName PlayerCharacterKeyName = "PlayerCharacter";

private:
	UPROPERTY()
	ARAITeam* Team;

	bool bStandsInCircle = false;
};
