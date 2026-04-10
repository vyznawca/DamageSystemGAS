// Adam Pawlewski - Damage System GAS

#include "DS_AttributeSet.h"

#include "Abilities/DS_AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DS_AttributeSet)

class UWorld;


UDS_AttributeSet::UDS_AttributeSet()
{
}

UWorld* UDS_AttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UDS_AbilitySystemComponent* UDS_AttributeSet::GetDSAbilitySystemComponent() const
{
	return Cast<UDS_AbilitySystemComponent>(GetOwningAbilitySystemComponent());
}

