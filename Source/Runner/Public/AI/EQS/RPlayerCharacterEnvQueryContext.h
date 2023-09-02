// Runner Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "RPlayerCharacterEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API URPlayerCharacterEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
