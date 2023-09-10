// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RCoreTypes.h"
#include "RTeam.generated.h"

class ARAICharacter;
struct FEnvQueryResult;
class UEnvQuery;
class ARPlayerCharacter;
class ARPickableItem;
/**
 * 
 */
UCLASS()
class RUNNER_API ARTeam : public AActor
{
    GENERATED_BODY()

public:
    void AddAIMember(ARAICharacter* NewMember);

    bool GetLocationOnCircle(FVector& Result, ARAICharacter* Char) const;
    bool IsEveryoneInCircle() const;
    bool IsPointInsideCircle(FVector Point) const;
    bool IsPointReachableByCharacter(const FVector Point, const ARAICharacter* Character) const;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    UEnvQuery* EnvQueryForBotsStandingShape;

    UPROPERTY(EditAnywhere)
    float CircleRadius = 500;

private:
    UPROPERTY()
    TArray<ARAICharacter*> AllMembers;

    bool bCircleExist = false;
    FVector CurrentCenterOfCircle;

    UPROPERTY()
    TArray<FVector> AllFreePointsOnCircle;

    int32 TotalNumberOfPointsOnCircle;

    UPROPERTY()
    TMap<ARAICharacter*, FVector> CharactersHasAlreadyTakenPlaceOnCircle;

    void BuildCircleAroundCharacter();
    void ClearCircleAroundCharacter();
    void OnFindAllPossiblePoints(TSharedPtr<FEnvQueryResult> Result);

    void DistributeAllPointsBetweenAI();
    bool AssignSuitablePointOnCircleToAI(ARAICharacter* Character);
    bool GetSuitablePointOnCircle(FVector& SuitablePointOnCircle, const ARAICharacter* Character) const;
    void AssignPointToAI(FVector Point, ARAICharacter* Character);

    UFUNCTION()
    void OnPlayerCharacterChangeMovementState(ERPlayerCharacterState MovementState);

    UFUNCTION()
    void OnPickableUpActorStateWasChanged(ERPickableItemState NewState);

    ARAICharacter* GetHoldedObjectCharacter() const;

    UPROPERTY()
    ARPlayerCharacter* PlayerCharacter;

    UPROPERTY()
    ARPickableItem* PickableItem;

    FCriticalSection CriticalSection;

};
