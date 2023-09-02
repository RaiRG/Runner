// Runner Game, All Rights Reserved.


#include "RAITeam.h"

#include "RAICharacter.h"
#include "RPlayerCharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogRAITeam, All, All);

ARAITeam::ARAITeam()
{
	PrimaryActorTick.bCanEverTick = false;
}


void ARAITeam::AddMember(ARAICharacter* NewMember)
{
	if (!NewMember->GetTeam())
	{
		AllMembers.AddUnique(NewMember);
		NewMember->SetTeam(this);
	}
}

bool ARAITeam::GetLocationOnShape(FVector& Result)
{
	if (AllPossiblePointsForStandingMembers.Num() == 0)
	{
		return false;
	}
	CriticalSection.Lock();
	Result = AllPossiblePointsForStandingMembers.Pop();
	UE_LOG(LogRAITeam, Display, TEXT("Result of GetLocationOnShape = %s"), *Result.ToString());
	CriticalSection.Unlock();
	return true;
}

bool ARAITeam::DoesEveryoneInCircle() const
{
	for (const auto Member : AllMembers)
	{
		if (!Member->GetStandsInCircle())
		{
			UE_LOG(LogRAITeam, Display, TEXT("DoesEveryoneInCircle is false for %s"), *Member->GetName());

			return false;
		}
		UE_LOG(LogRAITeam, Display, TEXT("DoesEveryoneInCircle is true for %s"), *Member->GetName());

	}
	UE_LOG(LogRAITeam, Display, TEXT("DoesEveryoneInCircle is true"));
	return true;
}

void ARAITeam::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AllAICharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARAICharacter::StaticClass(), AllAICharacters);
	for (const auto AIActor : AllAICharacters)
	{
		if (const auto AICharacter = Cast<ARAICharacter>(AIActor))
		{
			AddMember(AICharacter);
		}
	}

	auto PlayerPawn = Cast<ARPlayerCharacter>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ARPlayerCharacter::StaticClass()));
	PlayerPawn->PlayerCharacterChangeMovementState.AddDynamic(this, &ARAITeam::OnPlayerCharacterChangeMovementState);
}

void ARAITeam::OnPlayerCharacterChangeMovementState(bool bCanMove)
{
	if (!bCanMove)
	{
		if (AllMembers.Num() > 0)
		{
			UE_LOG(LogRAITeam, Display, TEXT("OnPlayerCharacterChangeMovementState"));
			CriticalSection.Lock();
			FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EnvQueryForBotsStandingShape);
			HidingSpotQueryRequest.Execute(
				EEnvQueryRunMode::AllMatching,
				this,
				&ARAITeam::OnFindAllPossiblePoints);
		}
	}
	else
	{
		AllPossiblePointsForStandingMembers.Empty();
	}
}

void ARAITeam::OnFindAllPossiblePoints(TSharedPtr<FEnvQueryResult> Result)
{
	AllPossiblePointsForStandingMembers.Empty();
	Result->GetAllAsLocations(AllPossiblePointsForStandingMembers);
	UE_LOG(LogRAITeam, Display, TEXT("AllPossiblePointsForStandingMembers Number = %i"),
	       AllPossiblePointsForStandingMembers.Num());
	CriticalSection.Unlock();
}
