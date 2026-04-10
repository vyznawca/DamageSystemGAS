// Adam Pawlewski - Damage System GAS

#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "Components/GameFrameworkComponent.h"

#include "DS_HealthComponent.generated.h"

struct FDS_CharacterData;
class UDS_AbilitySystemComponent;
class UDS_HealthSet;
class UObject;
struct FFrame;
struct FGameplayEffectSpec;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDS_Health_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FDS_Health_AttributeChanged, UDS_HealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDS_StartingAttributesApplied, UDS_HealthComponent*, HealthComponent);

/**
 * UDS_HealthComponent
 *
 *	An actor component used to handle anything related to health.
 */
UCLASS(MinimalAPI, Blueprintable, Meta=(BlueprintSpawnableComponent))
class UDS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDS_HealthComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the health component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "DS|Health")
	static UDS_HealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UDS_HealthComponent>() : nullptr); }

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "DS|Health")
	void InitializeWithAbilitySystem(UDS_AbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "DS|Health")
	void UninitializeFromAbilitySystem();

	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "DS|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "DS|Health")
	float GetMaxHealth() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "DS|Health")
	float GetHealthNormalized() const;

public:
	// Delegate fired when the health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FDS_Health_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FDS_Health_AttributeChanged OnMaxHealthChanged;

	//Broadcasted after applying starting attributes effect
	UPROPERTY(BlueprintAssignable)
	FDS_StartingAttributesApplied OnStartingAttributesApplied;

protected:
	virtual void OnUnregister() override;

	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

protected:
	// Ability system used by this component.
	UPROPERTY()
	TObjectPtr<UDS_AbilitySystemComponent> AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	TObjectPtr<const UDS_HealthSet> HealthSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RowType = "DS_CharacterData"))
	FDataTableRowHandle CharacterDataRowHandle;

	mutable const FDS_CharacterData* AttributesData;
    
protected:
    FActiveGameplayEffectHandle StartingAttributesEffectHandle;
	
public:
	UDS_AbilitySystemComponent* GetDSAbilitySystemComponent() const;
	
	const FDS_CharacterData* GetCharacterData() const;

	UFUNCTION(BlueprintPure)
	bool K2_GetCharacterData(FDS_CharacterData& OutCharacterData) const;
};

