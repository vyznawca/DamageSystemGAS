// Copyright Epic Games, Inc. All Rights Reserved.


#include "DS_DamageGameMode.h"
#include "ShooterUI.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ADS_DamageGameMode::BeginPlay()
{
	Super::BeginPlay();

	// create the UI
	ShooterUI = CreateWidget<UShooterUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ShooterUIClass);
	ShooterUI->AddToViewport(0);
}

