// Adam Pawlewski - Damage System GAS

#include "DamageSystem/Executions/DS_DamageExecution.h"

#include "DamageSystem/DS_Logs.h"
#include "DamageSystem/Attributes/DS_CombatSet.h"
#include "DamageSystem/Attributes/DS_HealthSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DS_DamageExecution)

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition BaseDamageDef;
	FGameplayEffectAttributeCaptureDefinition ResistanceDef;

	FDamageStatics()
	{
		BaseDamageDef = FGameplayEffectAttributeCaptureDefinition(UDS_CombatSet::GetBaseDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		ResistanceDef = FGameplayEffectAttributeCaptureDefinition(UDS_HealthSet::GetResistanceAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
	}
};

static FDamageStatics& DamageStatics()
{
	static FDamageStatics Statics;
	return Statics;
}

UDS_DamageExecution::UDS_DamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().BaseDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceDef);
}

void UDS_DamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Resistance = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ResistanceDef, EvaluateParameters, Resistance);

	float BaseDamage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaseDamageDef, EvaluateParameters, BaseDamage);
	
	// Clamping is done when damage is converted to -health
	const float DamageDone = FMath::Max( BaseDamage - Resistance, 0.0f);

	if (DamageDone > 0.0f)
	{
		UE_LOG(LogDS, Log, TEXT("Damage [%s] by %f - source %s"),
			*GetNameSafe(ExecutionParams.GetTargetAbilitySystemComponent() ? ExecutionParams.GetTargetAbilitySystemComponent()->GetOwnerActor() : nullptr),
			DamageDone,
			*GetNameSafe(ExecutionParams.GetSourceAbilitySystemComponent() ? ExecutionParams.GetSourceAbilitySystemComponent()->GetOwnerActor() : nullptr));
		
		// Apply a damage modifier, this gets turned into - health on the target
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UDS_HealthSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageDone));
	}
}