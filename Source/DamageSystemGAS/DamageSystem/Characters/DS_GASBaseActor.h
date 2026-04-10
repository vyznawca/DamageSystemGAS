// Adam Pawlewski - Damage System GAS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "DS_GASBaseActor.generated.h"

class UDS_AbilitySystemComponent;
class UDS_HealthComponent;

UCLASS(Blueprintable)
class DAMAGESYSTEMGAS_API ADS_GASBaseActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDS_HealthComponent> HealthComponent;

	// Health attribute set used by this actor.
	UPROPERTY()
	TObjectPtr<const class UDS_HealthSet> HealthSet;
	
public:	
	//Sets default values for this actor's properties
	ADS_GASBaseActor(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UDS_AbilitySystemComponent* GetDSAbilitySystemComponent() const;
	
protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Ability system component
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDS_AbilitySystemComponent> AbilitySystemComponent;
};
