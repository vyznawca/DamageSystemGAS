// Adam Pawlewski - Damage System GAS

#pragma once

#include "AbilitySystemComponent.h"
#include "DS_AttributeSet.h"
#include "NativeGameplayTags.h"

#include "DS_HealthSet.generated.h"


/**
 * UDS_HealthSet
 *
 *	Class that defines attributes that are necessary for taking damage.
 *	Attribute examples include: health, shields, and resistances.
 */
UCLASS(MinimalAPI, BlueprintType)
class UDS_HealthSet : public UDS_AttributeSet
{
	GENERATED_BODY()

public:

	UDS_HealthSet();

	ATTRIBUTE_ACCESSORS(UDS_HealthSet, Health);
	ATTRIBUTE_ACCESSORS(UDS_HealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UDS_HealthSet, Healing);
	ATTRIBUTE_ACCESSORS(UDS_HealthSet, Damage);
	ATTRIBUTE_ACCESSORS(UDS_HealthSet, Resistance);

	// Delegate when health changes due to damage/healing, some information may be missing on the client
	mutable FDS_AttributeEvent OnHealthChanged;

	// Delegate when max health changes
	mutable FDS_AttributeEvent OnMaxHealthChanged;

	// Delegate to broadcast when the health attribute reaches zero
	mutable FDS_AttributeEvent OnOutOfHealth;

protected:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Resistance(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// The current health attribute.  The health will be capped by the max health attribute.  Health is hidden from modifiers so only executions can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "DS|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	// The current max health attribute.  Max health is an attribute since gameplay effects can modify it.
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "DS|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resistance, Category = "DS|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Resistance;

	// Used to track when the health reaches 0.
	bool bOutOfHealth;

	// Store the health before any changes 
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

	// -------------------------------------------------------------------
	//	Meta Attribute (please keep attributes that aren't 'stateful' below 
	// -------------------------------------------------------------------

	// Incoming healing. This is mapped directly to +Health
	UPROPERTY(BlueprintReadOnly, Category="DS|Health", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Healing;

	// Incoming damage. This is mapped directly to -Health
	UPROPERTY(BlueprintReadOnly, Category="DS|Health", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;
};

