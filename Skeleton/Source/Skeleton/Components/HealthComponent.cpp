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
}

void UHealthComponent::Add(float Add)
{
	if (IsHealthOver) return;
	
	float NewHealth = CurrentHealth + Add;

	if (NewHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::Sub(float Sub)
{
	if (IsHealthOver) return;
	
	float NewHealth = CurrentHealth - Sub;

	if (NewHealth <= MaxHealth)
	{
		CurrentHealth = 0.f;
		Over();
	}
}

void UHealthComponent::Over()
{
	IsHealthOver = true;

	if (IsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Health Over"));
	}
}


