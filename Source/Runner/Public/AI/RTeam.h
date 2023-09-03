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
    
    bool TakeLocationOnCircle(FVector& Result, ARAICharacter* Char);
    bool IsEveryoneInCircle() const;
    bool IsPointInsideCircle(FVector Point) const;
protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    UEnvQuery* EnvQueryForBotsStandingShape;

    UPROPERTY(EditAnywhere)
    float CircleRadius = 500;

    UPROPERTY(EditAnywhere, meta =(ToolTip="Impact ot distibution of all points between characters"))
    bool bPrioritizeCharacterWithPickableItem = true;

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
    void DistibuteAllPointsBetweenAI();

    UFUNCTION()
    void OnPlayerCharacterChangeMovementState(ERPlayerCharacterState MovementState);

    UFUNCTION()
    void OnPickableUpActorStateWasChanged(ERPickableItemState NewState);

    ARAICharacter* GetHoldedObjectCharacter();

    UPROPERTY()
    ARPlayerCharacter* PlayerCharacter;

    UPROPERTY()
    ARPickableItem* PickableItem;

    FCriticalSection CriticalSection;

};
