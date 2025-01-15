#include "AttackComponent.h"

#include "WeaponComponent.h"
#include "AnimationComponent.h"
#include "SwordAnimationType.h"
#include "StateComponent.h"
#include "StaminaComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UAttackComponent::Init()
{
	World = GetWorld();
	Owner = GetOwner();
	if (!Owner) return;

	WeaponComponent = Owner->FindComponentByClass<UWeaponComponent>();
	AnimationComponent = Owner->FindComponentByClass<UAnimationComponent>();
	StateComponent = Owner->FindComponentByClass<UStateComponent>();
	StaminaComponent = Owner->FindComponentByClass<UStaminaComponent>();
	CharacterMovementComponent = Owner->FindComponentByClass<UCharacterMovementComponent>();

	UpdateWeapon();
}

void UAttackComponent::UpdateWeapon()
{
	if (!WeaponComponent) return;

	WeaponRight = WeaponComponent->GetWeaponHandRight();
	WeaponLeft = WeaponComponent->GetWeaponHandLeft();
}

void UAttackComponent::RightWeak()
{
	if (!AnimationComponent || !StateComponent) return;

	EStateType State = StateComponent->GetState();

	if (State == EStateType::ATTACK)
	{
		IsCombo = true;
		return;
	}
	
	if (State != EStateType::IDLE && State != EStateType::MOVE) return;

	ResetCombo();
	Attack(EAttackType::RIGHT_WEAK);
}

void UAttackComponent::RightStrong()
{
	if (!AnimationComponent || !StateComponent) return;

	EStateType State = StateComponent->GetState();
	if (State != EStateType::IDLE && State != EStateType::MOVE) return;

	ResetCombo();
	Attack(EAttackType::RIGHT_STRONG);
}

void UAttackComponent::LeftWeak()
{
	
}

void UAttackComponent::LeftStrong()
{
	
}

void UAttackComponent::Attack(EAttackType AttackType)
{
	if (!StaminaComponent) return;
	
	if (AttackType == EAttackType::NONE) return;
	
	switch (AttackType) {
	case EAttackType::LEFT_WEAK:
		if (StaminaComponent->GetIsStaminaOver()) return;
		StaminaComponent->Sub(StaminaWeakAttack);
		break;
	case EAttackType::RIGHT_WEAK:
		if (StaminaComponent->GetIsStaminaOver()) return;
		StaminaComponent->Sub(StaminaWeakAttack);
		break;
	case EAttackType::LEFT_STRONG:
		if (StaminaComponent->GetIsStaminaOver()) return;
		StaminaComponent->Sub(StaminaStrongAttack);
		break;
	case EAttackType::RIGHT_STRONG:
		if (StaminaComponent->GetIsStaminaOver()) return;
		StaminaComponent->Sub(StaminaStrongAttack);
		break;
	}
	
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::ATTACK);
	}
	
	Animation(AttackType);
}

void UAttackComponent::Animation(EAttackType AttackType)
{
	if (AttackType == EAttackType::NONE) return;
	if (!AnimationComponent) return;
	UpdateWeapon();
	
	switch (AttackType) {
	case EAttackType::RIGHT_WEAK:
		SwordAnimationWeak();
		break;
	case EAttackType::RIGHT_STRONG:
		SwordAnimationStrong();
		break;
	case EAttackType::LEFT_WEAK:
		break;
	case EAttackType::LEFT_STRONG:
		break;
	}
}

void UAttackComponent::SwordAnimationWeak()
{
	if (WeaponRight != EWeaponRightType::SWORD) return;

	switch (Combo)
		{
	case 0:
		AnimationComponent->PlaySword(ESwordAnimationType::SWORD_WEAK_ATTACK_0);
			break;
	case 1:
		AnimationComponent->PlaySword(ESwordAnimationType::SWORD_WEAK_ATTACK_1);
			break;
	case 2:
		AnimationComponent->PlaySword(ESwordAnimationType::SWORD_WEAK_ATTACK_2);
			break;
		}
	
	Combo++;
	if (Combo == 3) Combo = 0;
}

void UAttackComponent::SwordAnimationStrong()
{
	if (WeaponRight != EWeaponRightType::SWORD) return;

	switch (Combo)
	{
	case 0:
		AnimationComponent->PlaySword(ESwordAnimationType::SWORD_STRONG_ATTACK_0);
		break;
	}
	
	Combo++;
	if (Combo == 1) Combo = 0;
}

void UAttackComponent::AttackRotation()
{
	if (!CharacterMovementComponent || !World) return;
	
	CharacterMovementComponent->bAllowPhysicsRotationDuringAnimRootMotion = true;
	// CharacterMovementComponent->RotationRate = FRotator(CharacterMovementComponent->RotationRate.Pitch, CharacterMovementComponent->RotationRate.Yaw, CharacterMovementComponent->RotationRate.Roll * 2);

	FTimerHandle AttackRotationTimerHandle;
	World->GetTimerManager().SetTimer(AttackRotationTimerHandle, [&]()
		{
			if (!CharacterMovementComponent) return;
			CharacterMovementComponent->bAllowPhysicsRotationDuringAnimRootMotion = false;
		}, RotationDuration, false);
}

void UAttackComponent::CheckCombo()
{
	if (IsCombo)
	{
		Attack(EAttackType::RIGHT_WEAK);
		IsCombo = false;
	}
}

void UAttackComponent::AttackEnd()
{
	if (StateComponent)
	{
		StateComponent->SetState(EStateType::IDLE);
		
	}
	ResetCombo();
}

void UAttackComponent::ResetCombo()
{
	Combo = 0;
	IsCombo = false;
}



