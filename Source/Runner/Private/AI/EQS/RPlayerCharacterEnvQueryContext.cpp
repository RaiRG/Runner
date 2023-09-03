// Runner Game, All Rights Reserved.


#include "AI/EQS/RPlayerCharacterEnvQueryContext.h"

#include "RPlayerCharacter.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"

void URPlayerCharacterEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance,
    FEnvQueryContextData& ContextData) const
{
    const auto PlayerCharacter = UGameplayStatics::GetActorOfClass(GetWorld(), ARPlayerCharacter::StaticClass());
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerCharacter);
}
