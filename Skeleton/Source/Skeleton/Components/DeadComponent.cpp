#include "DeadComponent.h"

#include "AnimationComponent.h"
#include "InputCatcherComponent.h"
#include "PhysicsHelperComponent.h"
#include "StateComponent.h"


UDeadComponent::UDeadComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDeadComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UDeadComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;

	StateComponent = Owner->GetComponentByClass<UStateComponent>();
	PhysicsHelperComponent = Owner->GetComponentByClass<UPhysicsHelperComponent>();
	InputCatcherComponent = Owner->GetComponentByClass<UInputCatcherComponent>();
	AnimationComponent = Owner->GetComponentByClass<UAnimationComponent>();
}

void UDeadComponent::Dead()
{
	if (IsDead) return;
	IsDead = true;
	
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::DEAD);
	}

	if (InputCatcherComponent)
	{
		InputCatcherComponent->SetInput(false);
	}

	if (PhysicsHelperComponent)
	{
		PhysicsHelperComponent->EnablePhysics();
	}

	if (AnimationComponent)
	{
		AnimationComponent->Pause();
	}
}


