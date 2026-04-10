// Adam Pawlewski - Damage System GAS

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectComponents/CustomCanApplyGameplayEffectComponent.h"
#include "DS_CanApply_CheckResistance.generated.h"

/**
 * 
 */
UCLASS(DisplayName="Can Apply - Checks Resistance by Tags")
class DAMAGESYSTEMGAS_API UDS_CanApply_CheckResistance : public UCustomCanApplyGameplayEffectComponent
{
	GENERATED_BODY()
	
public:
	virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const override;
};
