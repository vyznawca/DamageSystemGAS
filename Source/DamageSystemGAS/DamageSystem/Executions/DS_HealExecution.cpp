// Adam Pawlewski - Damage System GAS

#include "DS_HealExecution.h"

#include "DamageSystem/DS_Logs.h"
#include "DamageSystem/Attributes/DS_CombatSet.h"
#include "DamageSystem/Attributes/DS_HealthSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DS_HealExecution)

struct FHealStatics
{
	FGameplayEffectAttributeCaptureDefinition BaseHealDef;
	FGameplayEffectAttributeCaptureDefinition ResistanceDef;

	FHealStatics()
	{
		BaseHealDef = FGameplayEffectAttributeCaptureDefinition(UDS_CombatSet::GetBaseHealAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		ResistanceDef = FGameplayEffectAttributeCaptureDefinition(UDS_HealthSet::GetResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
	}
};

static FHealStatics& HealStatics()
{
	static FHealStatics Statics;
	return Statics;
}

UDS_HealExecution::UDS_HealExecution()
{
	RelevantAttributesToCapture.Add(HealStatics().BaseHealDef);
	RelevantAttributesToCapture.Add(HealStatics().ResistanceDef);
}

void UDS_HealExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float BaseHeal = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealStatics().BaseHealDef, EvaluateParameters, BaseHeal);
	
	float Resistance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealStatics().ResistanceDef, EvaluateParameters, Resistance);
	
	const float HealingDone = FMath::Max(0.0f, BaseHeal - Resistance);

	if (HealingDone > 0.0f)
	{
		UE_LOG(LogDS, Log, TEXT("Heal [%s] by %f - source %s"),
			*GetNameSafe(ExecutionParams.GetTargetAbilitySystemComponent() ? ExecutionParams.GetTargetAbilitySystemComponent()->GetOwnerActor() : nullptr),
			BaseHeal,
			*GetNameSafe(ExecutionParams.GetSourceAbilitySystemComponent() ? ExecutionParams.GetSourceAbilitySystemComponent()->GetOwnerActor() : nullptr));
		
		// Apply a healing modifier, this gets turned into + health on the target
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UDS_HealthSet::GetHealingAttribute(), EGameplayModOp::Additive, HealingDone));
	}
}

