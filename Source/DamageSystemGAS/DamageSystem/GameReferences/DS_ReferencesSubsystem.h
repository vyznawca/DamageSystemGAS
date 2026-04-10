#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "DS_ReferencesSubsystem.generated.h"

class UGameplayEffect;
class UDataTable;

UCLASS(meta = (DisplayName = "Game References Subsystem"))
class DAMAGESYSTEMGAS_API UDS_ReferencesSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	static UDS_ReferencesSubsystem& Get();

	void Reset();

	UDataTable* GetDamageDataDataTable() const;
	
	TSubclassOf<UGameplayEffect> GetStartingAttributesEffectClass() const;

protected:
	void LoadTable(const TSoftObjectPtr<UDataTable>& SoftDataTableReference, UDataTable*& OutDataTable);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	mutable UDataTable* DamageDataDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    mutable TSubclassOf<UGameplayEffect> StartingAttributesEffect;
};