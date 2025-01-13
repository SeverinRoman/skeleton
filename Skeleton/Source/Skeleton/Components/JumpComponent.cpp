#include "JumpComponent.h"

#include "AnimationComponent.h"
#include "StateComponent.h"
#include "StaminaComponent.h"

#include "AnimationType.h"

#include "GameFramework/Character.h"


UJumpComponent::UJumpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJumpComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UJumpComponent::Init()
{
	Owner = GetOwner();
	if (!Owner) return;

	StateComponent = Owner->FindComponentByClass<UStateComponent>();
	AnimationComponent = Owner->FindComponentByClass<UAnimationComponent>();
	StaminaComponent = Owner->FindComponentByClass<UStaminaComponent>();
	Character = Cast<ACharacter>(Owner);
}

void UJumpComponent::Try()
{
	if (!StateComponent || !StaminaComponent) return;

	EStateType State = StateComponent->GetState();
	if (State != EStateType::MOVE) return;

	if (StaminaComponent->GetStamina() < Stamina) return;
	StaminaComponent->Sub(Stamina);
	
	Jump();
}

void UJumpComponent::Jump()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::JUMP);
	}
	
	if (AnimationComponent)
	{
		AnimationComponent->PlayBase(EAnimationType::JUMP);
	}
	
	if(Character)
	{
		Character->Jump();
	}
}

void UJumpComponent::End()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::FALLING);
	}
}
