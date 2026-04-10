// Adam Pawlewski - Damage System GAS

#include "DS_CombatSet.h"

#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DS_CombatSet)

class FLifetimeProperty;

UDS_CombatSet::UDS_CombatSet()
	: BaseDamage(0.0f)
	, BaseHeal(0.0f)
{
}

void UDS_CombatSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDS_CombatSet, BaseDamage, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDS_CombatSet, BaseHeal, COND_OwnerOnly, REPNOTIFY_Always);
}

void UDS_CombatSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDS_CombatSet, BaseDamage, OldValue);
}

void UDS_CombatSet::OnRep_BaseHeal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDS_CombatSet, BaseHeal, OldValue);
}

