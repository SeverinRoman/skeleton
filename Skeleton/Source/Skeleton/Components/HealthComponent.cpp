#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UHealthComponent::Init()
{
	CurrentHealth = StartHealth;

	OnHealthChange.Broadcast();
}

void UHealthComponent::Add(float Add)
{
	if (IsHealthOver) return;
	
	float NewHealth = CurrentHealth + Add;

	if (NewHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}else
	{
		CurrentHealth = NewHealth;
	}

	OnHealthChange.Broadcast();
}

void UHealthComponent::Sub(float Sub)
{
	if (IsHealthOver) return;
	
	float NewHealth = CurrentHealth - Sub;

	if (NewHealth <= 0.f)
	{
		CurrentHealth = 0.f;
		Over();
	}else
	{
		CurrentHealth = NewHealth;
	}

	OnHealthChange.Broadcast();
}

void UHealthComponent::Over()
{
	IsHealthOver = true;

	if (IsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Health Over"));
	}
}


