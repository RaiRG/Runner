// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RBaseCharacter.h"
#include "RAICharacter.generated.h"


class UBehaviorTree;
class ARTeam;
UCLASS()
class RUNNER_API ARAICharacter : public ARBaseCharacter
{
    GENERATED_BODY()

public:
    ARAICharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    UBehaviorTree* BehaviorTreeAsset;
    
    void SetTeam(ARTeam* NewTeam) { Team = NewTeam; }
    ARTeam* GetTeam() const { return Team; }

    bool GetStandsInCircle() const { return bStandsInCircle; }
    void SetStandsInCircle(bool Val) { bStandsInCircle = Val; }

    virtual bool HoldObject(AActor* ActorForHolding) override;
    virtual void DropHoldedActor(FVector Impulse = FVector()) override;
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    FName PickableItemKeyName = "PickableSphere";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    FName PlayerCharacterKeyName = "PlayerCharacter";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    FName PatrolPositionKeyName = "PatrolPosition";

private:
    bool bStandsInCircle = false;

    UPROPERTY()
    ARTeam* Team;
};
