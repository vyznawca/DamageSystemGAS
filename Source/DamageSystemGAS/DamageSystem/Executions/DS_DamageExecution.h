// Adam Pawlewski - Damage System GAS

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DS_DamageExecution.generated.h"

// Execution used to deal damage
UCLASS()
class DAMAGESYSTEMGAS_API UDS_DamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UDS_DamageExecution();
	
protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
