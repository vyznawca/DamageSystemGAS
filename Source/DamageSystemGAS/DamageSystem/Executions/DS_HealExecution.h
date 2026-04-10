// Adam Pawlewski - Damage System GAS

#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "DS_HealExecution.generated.h"

class UObject;


//Execution used by gameplay effects to apply healing to the health attributes.
UCLASS()
class UDS_HealExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UDS_HealExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
