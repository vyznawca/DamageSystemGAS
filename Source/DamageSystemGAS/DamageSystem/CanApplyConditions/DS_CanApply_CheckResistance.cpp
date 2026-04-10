// Adam Pawlewski - Damage System GAS


#include "DamageSystem/CanApplyConditions/DS_CanApply_CheckResistance.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"
#include "DamageSystem/DS_Tags.h"
#include "DamageSystem/Attributes/DS_HealthSet.h"

bool UDS_CanApply_CheckResistance::CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const
{
	const FGameplayTagContainer* SourceTags = GESpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = GESpec.CapturedTargetTags.GetAggregatedTags();
	bool bSuccess = false;
	
	float FireResistanceValue = UAbilitySystemBlueprintLibrary::EvaluateAttributeValueWithTags(ActiveGEContainer.Owner, UDS_HealthSet::GetResistanceAttribute(), *SourceTags, *TargetTags, bSuccess);

	return FireResistanceValue <= 0.f;
}
