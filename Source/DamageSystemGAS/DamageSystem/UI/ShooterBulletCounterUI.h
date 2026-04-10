// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterBulletCounterUI.generated.h"

class UTextBlock;
/**
 *  Simple bullet counter UI widget for a first person shooter game
 */
UCLASS(abstract)
class DAMAGESYSTEMGAS_API UShooterBulletCounterUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/** Allows Blueprint to update sub-widgets with the new bullet count */
	UFUNCTION(BlueprintImplementableEvent, Category="Shooter", meta=(DisplayName = "UpdateBulletCounter"))
	void BP_UpdateBulletCounter(int32 MagazineSize, int32 BulletCount);

	/** Allows Blueprint to update sub-widgets with the new life total and play a damage effect on the HUD */
	UFUNCTION(BlueprintImplementableEvent, Category="Shooter", meta=(DisplayName = "Damaged"))
	void BP_Damaged(float LifePercent);
	
	UFUNCTION(Category="DS|Damage")
	void SetupDamageAndHealTexts(int32 DamagePerHit, int32 HealPerHit);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;
};
