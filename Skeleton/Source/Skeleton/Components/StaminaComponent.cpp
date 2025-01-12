#include "StaminaComponent.h"


UStaminaComponent::UStaminaComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UStaminaComponent::Init()
{
	CurrentStamina = StartStamina;

	OnStaminaChange.Broadcast();
}

void UStaminaComponent::Add(float Add)
{
	if (IsStaminaOver) return;
	
	float NewHealth = CurrentStamina + Add;

	if (NewHealth >= MaxStamina)
	{
		CurrentStamina = MaxStamina;
	}else
	{
		CurrentStamina = NewHealth;
	}

	OnStaminaChange.Broadcast();
}

void UStaminaComponent::Sub(float Sub)
{
	if (IsStaminaOver) return;
	
	float NewHealth = CurrentStamina - Sub;

	if (NewHealth <= 0.f)
	{
		CurrentStamina = 0.f;
		Over();
	}else
	{
		CurrentStamina = NewHealth;
	}

	OnStaminaChange.Broadcast();
}

void UStaminaComponent::Over()
{
	IsStaminaOver = true;

	if (IsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Health Over"));
	}
}

