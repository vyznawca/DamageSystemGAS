#include "DS_ReferencesSubsystem.h"

#include "DS_ReferencesSettings.h"
#include "GameplayEffect.h"

void UDS_ReferencesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	Reset();
}

void UDS_ReferencesSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UDS_ReferencesSubsystem& UDS_ReferencesSubsystem::Get()
{
	UDS_ReferencesSubsystem* const ReferenceSubsystem = GEngine->GetEngineSubsystem<UDS_ReferencesSubsystem>();
	check(ReferenceSubsystem);

	return *ReferenceSubsystem;
}

void UDS_ReferencesSubsystem::Reset()
{
	//Here call things that needs to be loaded at editor or game start with LoadTable func
}

UDataTable* UDS_ReferencesSubsystem::GetDamageDataDataTable() const
{
	if (!DamageDataDataTable)
	{
		DamageDataDataTable = UDS_ReferencesSettings::Get().DamageDataDataTableSoft.LoadSynchronous();
	}

	return DamageDataDataTable;
}

TSubclassOf<UGameplayEffect> UDS_ReferencesSubsystem::GetStartingAttributesEffectClass() const
{
	if (!StartingAttributesEffect)
	{
		StartingAttributesEffect = UDS_ReferencesSettings::Get().StartingAttributesEffect.LoadSynchronous();
	}

	return StartingAttributesEffect;
}

void UDS_ReferencesSubsystem::LoadTable(const TSoftObjectPtr<UDataTable>& SoftDataTableReference, UDataTable*& OutDataTable)
{
	OutDataTable = SoftDataTableReference.LoadSynchronous();
}
