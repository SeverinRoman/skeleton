#include "Components/DodgeComponent.h"

#include "AnimationComponent.h"
#include "StateComponent.h"

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
}

void UDodgeComponent::Dodge()
{
	if (!StateComponent) return;

	EStateType State = StateComponent->GetState();

	if (State == EStateType::IDLE || State == EStateType::MOVE)
	{
		DodgeStart();
	}
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

