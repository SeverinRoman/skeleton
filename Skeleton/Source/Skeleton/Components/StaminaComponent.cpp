#include "StaminaComponent.h"

#include "MoveComponent.h"
#include "StateComponent.h"


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
	Owner = GetOwner();

	if (Owner)
	{
		World = GetOwner()->GetWorld();
		
		StateComponent = Owner->GetComponentByClass<UStateComponent>();
		MoveComponent = Owner->GetComponentByClass<UMoveComponent>();
	}
	
	CurrentStamina = StartStamina;
	OnStaminaChange.Broadcast();
	
	if (World)
	{
		World->GetTimerManager().SetTimer(RegenerationTimerHandle, this, &UStaminaComponent::Regeneration, RegenerationDelay, true);
	}
}

void UStaminaComponent::Regeneration()
{
	if (!StateComponent || !MoveComponent) return;

	if (Deterioration()) return;

	if (CurrentStamina == MaxStamina) return;

	EStateType State = StateComponent->GetState();

	if (State != EStateType::IDLE && State != EStateType::MOVE) return;

	Add(1.f);
}

bool UStaminaComponent::Deterioration()
{
	if (MoveComponent->GetMove() == EMoveType::SPRINT && StateComponent->GetSpeed() > 0.f)
	{
		if (CurrentStamina <= 0.f) return false;
	
		Sub(1.f);
		return true;
	}
	
	return false;
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
	if (IsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Health Over"));
	}

	OnStaminaEnd.Broadcast();
}

