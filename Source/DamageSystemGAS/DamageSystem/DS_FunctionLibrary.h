// Adam Pawlewski - Damage System GAS

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DS_FunctionLibrary.generated.h"

struct FDS_DamageTypeData;
struct FGameplayTag;
enum class EDS_AmmoType : uint8;
/**
 * 
 */
UCLASS()
class DAMAGESYSTEMGAS_API UDS_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DS|Ammo")
	static FDS_DamageTypeData K2_GetAmmoTypeData(const FGameplayTag& InAmmoTag);
	
	static FDS_DamageTypeData* GetAmmoTypeData(const FGameplayTag& InAmmoTag);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DS|Ammo")
	static FLinearColor GetColorForAmmo(const FGameplayTag& InAmmoTag);
	
	UFUNCTION(BlueprintCallable, Category = "DS|Log")
	static void DS_UELOG_EffectStarted(FString InEffectName, UObject* InTarget);
	
	UFUNCTION(BlueprintCallable, Category = "DS|Log")
	static void DS_UELOG_EffectEnded(FString InEffectName, UObject* InTarget);
};
