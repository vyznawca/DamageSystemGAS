// Adam Pawlewski - Damage System GAS


#include "DamageSystem/UI/DS_CharacterOverheadInfo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/DS_AbilitySystemComponent.h"
#include "Attributes/DS_HealthSet.h"
#include "Characters/DS_HealthComponent.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "DamageSystem/DS_Structs.h"

void UDS_CharacterOverheadInfo::SetupTexts(UDS_HealthComponent* InHealthComponent)
{
	checkf(InHealthComponent, TEXT("No Valid Health Component in UDS_CharacterOverheadInfo::SetupTexts"));
	
	const FDS_CharacterData* CharacterData = InHealthComponent->GetCharacterData();
	checkf(CharacterData, TEXT("No Valid CharacterData in UDS_CharacterOverheadInfo::SetupTexts"));
	
	NameText->SetText(InHealthComponent->GetCharacterData()->DisplayName);
	HealthText->SetVisibility(ESlateVisibility::HitTestInvisible);
	HealthText->SetText( FText::AsNumber(InHealthComponent->GetHealth()));

	InHealthComponent->OnHealthChanged.AddUniqueDynamic(this, &UDS_CharacterOverheadInfo::OnHealthChanged);
	InHealthComponent->OnStartingAttributesApplied.AddUniqueDynamic(this, &UDS_CharacterOverheadInfo::OnStartingAttributesApplied);

	SetupResistanceValues(InHealthComponent);
}

void UDS_CharacterOverheadInfo::SetupResistanceValues(UDS_HealthComponent* InHealthComponent)
{
	if (!IsValid(InHealthComponent))
	{
		return;
	}
	
	//Physical Resistance
	FGameplayTagContainer SourceTags = FGameplayTagContainer(GTag_DS_DamageType_Physical_Basic);
	FGameplayTagContainer TargetTags;
	bool bSuccess = false;
	float PhysicalResistanceValue = UAbilitySystemBlueprintLibrary::EvaluateAttributeValueWithTags(InHealthComponent->GetDSAbilitySystemComponent(), UDS_HealthSet::GetResistanceAttribute(), SourceTags, TargetTags, bSuccess);

	PhysicalResistanceHB->SetVisibility(PhysicalResistanceValue != 0.f ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	PhysicalResistanceText->SetText(FText::AsNumber(PhysicalResistanceValue));

	//Fire Resistance
	SourceTags = FGameplayTagContainer(GTag_DS_DamageType_Elemental_Fire);
	float FireResistanceValue = UAbilitySystemBlueprintLibrary::EvaluateAttributeValueWithTags(InHealthComponent->GetDSAbilitySystemComponent(), UDS_HealthSet::GetResistanceAttribute(), SourceTags, TargetTags, bSuccess);

	FireResistanceHB->SetVisibility(FireResistanceValue != 0.f ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	FireResistanceText->SetText(FText::AsNumber(FireResistanceValue));

	//Water Resistance
	SourceTags = FGameplayTagContainer(GTag_DS_DamageType_Elemental_Water);
	float WaterResistanceValue = UAbilitySystemBlueprintLibrary::EvaluateAttributeValueWithTags(InHealthComponent->GetDSAbilitySystemComponent(), UDS_HealthSet::GetResistanceAttribute(), SourceTags, TargetTags, bSuccess);

	WaterResistanceHB->SetVisibility(WaterResistanceValue != 0.f ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	WaterResistanceText->SetText(FText::AsNumber(WaterResistanceValue));

	//Healing Resistance
	SourceTags = FGameplayTagContainer(GTag_DS_DamageType_Healing);
	float HealResistanceValue = UAbilitySystemBlueprintLibrary::EvaluateAttributeValueWithTags(InHealthComponent->GetDSAbilitySystemComponent(), UDS_HealthSet::GetResistanceAttribute(), SourceTags, TargetTags, bSuccess);

	HealResistanceHB->SetVisibility(HealResistanceValue != 0.f ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	HealResistanceText->SetText(FText::AsNumber(HealResistanceValue));
}

void UDS_CharacterOverheadInfo::OnHealthChanged(UDS_HealthComponent* HealthComponent, float OldValue, float NewValue, AActor* Instigator)
{
	HealthText->SetText( FText::AsNumber(NewValue));
}

void UDS_CharacterOverheadInfo::OnStartingAttributesApplied(UDS_HealthComponent* HealthComponent)
{
	SetupResistanceValues(HealthComponent);
}
