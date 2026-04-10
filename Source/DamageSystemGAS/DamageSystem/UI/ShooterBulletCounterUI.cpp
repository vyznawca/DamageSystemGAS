// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterBulletCounterUI.h"

#include "Components/TextBlock.h"

void UShooterBulletCounterUI::SetupDamageAndHealTexts(int32 DamagePerHit, int32 HealPerHit)
{
	DamageText->SetVisibility(DamagePerHit != 0 || HealPerHit != 0 ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	
	DamageText->SetText( FText::Format(
		FText::FromString("Damage: {Damage} | Heal: {Heal}"),
		FFormatNamedArguments{
			{ "Damage", FText::AsNumber(DamagePerHit) },
			{ "Heal", FText::AsNumber(HealPerHit) }
		}
	));
}
