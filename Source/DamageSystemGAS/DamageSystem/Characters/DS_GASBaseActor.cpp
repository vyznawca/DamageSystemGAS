// Adam Pawlewski - Damage System GAS

#include "DS_GASBaseActor.h"

#include "AbilitySystemComponent.h"
#include "DS_HealthComponent.h"
#include "Abilities/DS_AbilitySystemComponent.h"
#include "Attributes/DS_HealthSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DS_GASBaseActor)

// Sets default values
ADS_GASBaseActor::ADS_GASBaseActor(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	HealthComponent = CreateDefaultSubobject<UDS_HealthComponent>(TEXT("HealthComponent"));
	
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UDS_AbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HealthSet = CreateDefaultSubobject<UDS_HealthSet>(TEXT("HealthSet"));
}

void ADS_GASBaseActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

UAbilitySystemComponent* ADS_GASBaseActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UDS_AbilitySystemComponent* ADS_GASBaseActor::GetDSAbilitySystemComponent() const
{
	return Cast<UDS_AbilitySystemComponent>(GetAbilitySystemComponent());
}

// Called when the game starts or when spawned
void ADS_GASBaseActor::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->InitializeWithAbilitySystem(GetDSAbilitySystemComponent());
}

