// Adam Pawlewski - Damage System GAS

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CharacterOverheadInfo.generated.h"

class UHorizontalBox;
class UDS_HealthComponent;
struct FDS_CharacterData;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DAMAGESYSTEMGAS_API UDS_CharacterOverheadInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetupTexts(UDS_HealthComponent* InHealthComponent);

	UFUNCTION()
	void OnHealthChanged(UDS_HealthComponent* HealthComponent, float OldValue, float NewValue, AActor* Instigator);

	UFUNCTION()
	void OnStartingAttributesApplied(UDS_HealthComponent* HealthComponent);
	
private:
	void SetupResistanceValues(UDS_HealthComponent* InHealthComponent);
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* PhysicalResistanceHB;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PhysicalResistanceText;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* FireResistanceHB;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FireResistanceText;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* WaterResistanceHB;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaterResistanceText;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HealResistanceHB;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealResistanceText;
};
