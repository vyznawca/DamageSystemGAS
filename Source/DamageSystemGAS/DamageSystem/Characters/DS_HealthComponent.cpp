// Adam Pawlewski - Damage System GAS

#include "DS_HealthComponent.h"

#include "DS_Logs.h"
#include "Attributes/DS_HealthSet.h"
#include "DS_Structs.h"
#include "DS_Tags.h"
#include "Abilities/DS_AbilitySystemComponent.h"
#include "GameReferences/DS_ReferencesSubsystem.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DS_HealthComponent)


UDS_HealthComponent::UDS_HealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	HealthSet = nullptr;
}

void UDS_HealthComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();

	Super::OnUnregister();
}

void UDS_HealthComponent::InitializeWithAbilitySystem(UDS_AbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("DS_HealthComponent: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("DS_HealthComponent: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	HealthSet = AbilitySystemComponent->GetSet<UDS_HealthSet>();
	if (!HealthSet)
	{
		UE_LOG(LogTemp, Error, TEXT("DS_HealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
	HealthSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);

	//Starting attributes
	if (const TSubclassOf<UGameplayEffect> SetStartingAttributesEffect = UDS_ReferencesSubsystem::Get().GetStartingAttributesEffectClass())
	{
		FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
		Context.AddSourceObject(GetOwner());

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(SetStartingAttributesEffect, 1.0f, Context);
		if (SpecHandle.IsValid() && GetCharacterData())
		{
			FGameplayEffectSpec* Spec = SpecHandle.Data.Get();

			//We need to set every tag that effect is expecting or its going to throw an error
			TArray<FGameplayTag> AllAttributesInEffect = {GTag_DS_Effect_SetByCaller_MaxHealth, GTag_DS_DamageType_Physical_Basic, GTag_DS_DamageType_Elemental_Fire, GTag_DS_DamageType_Elemental_Water, GTag_DS_DamageType_Healing};
			
			for (const FDS_TagFloatPair& Attribute : GetCharacterData()->StartingAttributes)
			{
				Spec->SetSetByCallerMagnitude(Attribute.Tag, Attribute.Value);
				AllAttributesInEffect.Remove(Attribute.Tag);
			}

			for (const FGameplayTag& Tag : AllAttributesInEffect)
			{
				Spec->SetSetByCallerMagnitude(Tag, 0.f);
			}

			StartingAttributesEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
            OnStartingAttributesApplied.Broadcast(this);
		}
	}
	
	AbilitySystemComponent->SetNumericAttributeBase(UDS_HealthSet::GetHealthAttribute(), HealthSet->GetMaxHealth());

	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
	OnMaxHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
}

void UDS_HealthComponent::UninitializeFromAbilitySystem()
{
	if (HealthSet)
	{
		HealthSet->OnHealthChanged.RemoveAll(this);
		HealthSet->OnMaxHealthChanged.RemoveAll(this);
		HealthSet->OnOutOfHealth.RemoveAll(this);
	}

	HealthSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float UDS_HealthComponent::GetHealth() const
{
	return (HealthSet ? HealthSet->GetHealth() : 0.0f);
}

float UDS_HealthComponent::GetMaxHealth() const
{
	return (HealthSet ? HealthSet->GetMaxHealth() : 0.0f);
}

float UDS_HealthComponent::GetHealthNormalized() const
{
	if (HealthSet)
	{
		const float Health = HealthSet->GetHealth();
		const float MaxHealth = HealthSet->GetMaxHealth();

		return ((MaxHealth > 0.0f) ? (Health / MaxHealth) : 0.0f);
	}

	return 0.0f;
}

void UDS_HealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	UE_LOG(LogDS, Log, TEXT("New Health Value - [%s] - value changed %f -> %f"),	*GetNameSafe(AbilitySystemComponent->GetOuter()), OldValue, NewValue);
	OnHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UDS_HealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UDS_HealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	UE_LOG(LogDS, Log, TEXT("Dead - [%s]"),	*GetNameSafe(AbilitySystemComponent->GetOuter()));
	GetOwner()->Destroy();
}

UDS_AbilitySystemComponent* UDS_HealthComponent::GetDSAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const FDS_CharacterData* UDS_HealthComponent::GetCharacterData() const
{
	if (!AttributesData)
	{
		AttributesData = CharacterDataRowHandle.GetRow<FDS_CharacterData>("UDS_HealthComponent::GetCharacterData()");
	}

	return AttributesData;
}

bool UDS_HealthComponent::K2_GetCharacterData(FDS_CharacterData& OutCharacterData) const
{
	if (const FDS_CharacterData* CharacterDataPtr = GetCharacterData())
	{
		OutCharacterData = *CharacterDataPtr;
		return true;
	}

	return false;
}


