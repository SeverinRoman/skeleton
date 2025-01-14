#include "AttackComponent.h"

#include "WeaponComponent.h"
#include "AnimationComponent.h"
#include "SwordAnimationType.h"
#include "StateComponent.h"


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
	AActor* Owner = GetOwner();
	if (!Owner) return;

	WeaponComponent = Owner->FindComponentByClass<UWeaponComponent>();
	AnimationComponent = Owner->FindComponentByClass<UAnimationComponent>();
	StateComponent = Owner->FindComponentByClass<UStateComponent>();

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
	
	Attack(EAttackType::RIGHT_WEAK);
}

void UAttackComponent::RightStrong()
{
	
}

void UAttackComponent::LeftWeak()
{
	
}

void UAttackComponent::LeftStrong()
{
	
}

void UAttackComponent::Attack(EAttackType AttackType)
{
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
	case EAttackType::LEFT_WEAK:
		break;
	case EAttackType::RIGHT_WEAK:
		SwordAnimation();
		break;
	case EAttackType::LEFT_STRONG:
		break;
	case EAttackType::RIGHT_STRONG:
		break;
	}
}

void UAttackComponent::SwordAnimation()
{
	if (WeaponRight != EWeaponRightType::SWORD) return;
	UE_LOG(LogTemp, Warning, TEXT("UAttackComponent::SwordAnimation %d"), Combo);
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
	if (StateComponent && !IsCombo || Combo == 0)
	{
		StateComponent->SetState(EStateType::IDLE);
		Combo = 0;
	}
}



