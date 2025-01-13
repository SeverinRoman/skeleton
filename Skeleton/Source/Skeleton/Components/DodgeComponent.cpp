#include "Components/DodgeComponent.h"

#include "AnimationComponent.h"
#include "StateComponent.h"
#include "StaminaComponent.h"

#include "AnimationType.h"


UDodgeComponent::UDodgeComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}

void UDodgeComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UDodgeComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;

	AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();
	StateComponent = Owner->GetComponentByClass<UStateComponent>();
	StaminaComponent = Owner->GetComponentByClass<UStaminaComponent>();
}

void UDodgeComponent::Dodge()
{
	if (!StateComponent && StaminaComponent) return;

	EStateType State = StateComponent->GetState();

	if (State != EStateType::IDLE && State != EStateType::MOVE) return;

	if (StaminaComponent->GetStamina() < Stamina) return;
	
	StaminaComponent->Sub(Stamina);
	DodgeStart();
}

void UDodgeComponent::DodgeStart()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::DODGE);
	}
	
	if (AnimationComponent)
	{
		AnimationComponent->PlayBase(EAnimationType::DODGE);
	}
}

void UDodgeComponent::DodgeEnd()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::IDLE);
	}
}

