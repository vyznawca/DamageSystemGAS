// Adam Pawlewski - Damage System GAS

#pragma once
#include "DS_Tags.h"
#include "GameplayTagContainer.h"

#include "DS_Structs.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDS_DamageTypeData : public FTableRowBase
{
	GENERATED_BODY()

	FDS_DamageTypeData() {}

	static const FDS_DamageTypeData Empty;

	//Remember to name row the same as this tag value, this way we can find rows in DT in easier and faster way
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "DS.DamageType"))
	FGameplayTag DamageTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Color = FLinearColor::White;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UGameplayEffect> EffectToApplyOnHit;
};


USTRUCT(BlueprintType)
struct FDS_TagFloatPair
{
	GENERATED_BODY()

	FDS_TagFloatPair()  {}
	
	FDS_TagFloatPair(FGameplayTag InTag, float InValue) : Tag(InTag), Value(InValue) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Tag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value = 0.f;
};

USTRUCT(BlueprintType)
struct FDS_CharacterData : public FTableRowBase
{
	GENERATED_BODY()

	FDS_CharacterData() {}

	static const FDS_CharacterData Empty;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDS_TagFloatPair> StartingAttributes = {FDS_TagFloatPair(GTag_DS_Effect_SetByCaller_MaxHealth, 100.f)};
};

