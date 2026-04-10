// Adam Pawlewski - Damage System GAS


#include "DamageSystem/DS_FunctionLibrary.h"

#include "DS_Logs.h"
#include "DS_Structs.h"
#include "DS_Tags.h"
#include "GameplayEffect.h"
#include "GameReferences/DS_ReferencesSubsystem.h"

FDS_DamageTypeData* UDS_FunctionLibrary::GetAmmoTypeData(const FGameplayTag& InAmmoTag)
{
	if (const UDataTable* DamageDataDT = UDS_ReferencesSubsystem::Get().GetDamageDataDataTable(); IsValid(DamageDataDT))
	{
		if (FDS_DamageTypeData* FoundRow = DamageDataDT->FindRow<FDS_DamageTypeData>(InAmmoTag.GetTagName(), "UDS_FunctionLibrary::GetAmmoTypeData"))
		{
			return FoundRow;
		}
	}

	return nullptr;
}

FDS_DamageTypeData UDS_FunctionLibrary::K2_GetAmmoTypeData(const FGameplayTag& InAmmoTag)
{
	FDS_DamageTypeData* Data = GetAmmoTypeData(InAmmoTag);
	if(Data)
	{
		return *Data;
	}

	return FDS_DamageTypeData::Empty;
}

FLinearColor UDS_FunctionLibrary::GetColorForAmmo(const FGameplayTag& InAmmoTag)
{
	if (const UDataTable* DamageDataDT = UDS_ReferencesSubsystem::Get().GetDamageDataDataTable(); IsValid(DamageDataDT))
	{
		if (FDS_DamageTypeData* FoundRow = DamageDataDT->FindRow<FDS_DamageTypeData>(InAmmoTag.GetTagName(), "UDS_FunctionLibrary::GetColorForAmmo"))
		{
			return FoundRow->Color;
		}
	}

	return FLinearColor::White;
}

void UDS_FunctionLibrary::DS_UELOG_EffectStarted(FString InEffectName, UObject* InTarget)
{
	UE_LOG(LogDS, Log, TEXT("Effect [%s] applied to [%s]"),	*InEffectName, *GetNameSafe(InTarget));
}

void UDS_FunctionLibrary::DS_UELOG_EffectEnded(FString InEffectName, UObject* InTarget)
{
	UE_LOG(LogDS, Log, TEXT("Effect [%s] removed from [%s]"), *InEffectName, *GetNameSafe(InTarget));
}
