#include "DS_ReferencesSettings.h"
#include "DS_ReferencesSubsystem.h"

const UDS_ReferencesSettings& UDS_ReferencesSettings::Get()
{
	return *CastChecked<UDS_ReferencesSettings>(UDS_ReferencesSettings::StaticClass()->GetDefaultObject());
}

#if WITH_EDITOR
void UDS_ReferencesSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UDS_ReferencesSubsystem* const GameReferencesSubsystem = GEngine->GetEngineSubsystem<UDS_ReferencesSubsystem>();
	check(GameReferencesSubsystem);

	GameReferencesSubsystem->Reset();
}
#endif