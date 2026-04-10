// Adam Pawlewski - Damage System GAS

#pragma once

#include "AbilitySystemComponent.h"
#include "DS_AttributeSet.h"

#include "DS_CombatSet.generated.h"


/**
 * UDS_CombatSet
 *
 *  Class that defines attributes that are necessary for applying damage or healing.
 *	Attribute examples include: damage, healing, attack power, and shield penetrations.
 */
UCLASS(BlueprintType)
class UDS_CombatSet : public UDS_AttributeSet
{
	GENERATED_BODY()

public:
	UDS_CombatSet();

	ATTRIBUTE_ACCESSORS(UDS_CombatSet, BaseDamage);
	ATTRIBUTE_ACCESSORS(UDS_CombatSet, BaseHeal);

protected:
	UFUNCTION()
	void OnRep_BaseDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BaseHeal(const FGameplayAttributeData& OldValue);

private:
	// The base amount of damage to apply in the damage execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "DS|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;

	// The base amount of healing to apply in the heal execution.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseHeal, Category = "DS|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHeal;
};
