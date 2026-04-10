#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DS_ReferencesSettings.generated.h"

class UDataTable;
class UGameplayEffect;


UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Damage System - References"))
class DAMAGESYSTEMGAS_API UDS_ReferencesSettings final : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UDS_ReferencesSettings& Get();

#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(EditAnywhere, BlueprintReadOnly, config, meta = (RowType = "DS_DamageTypeData"))
	TSoftObjectPtr<UDataTable> DamageDataDataTableSoft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, config)
	TSoftClassPtr<UGameplayEffect> StartingAttributesEffect;
};