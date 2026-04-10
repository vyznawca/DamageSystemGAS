// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DS_GameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class ADS_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADS_GameMode();
};



