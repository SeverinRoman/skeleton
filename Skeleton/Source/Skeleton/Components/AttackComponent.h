#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


class UWeaponComponent;
class UAnimationComponent;
class UStateComponent;
class UStaminaComponent;
class UCharacterMovementComponent;

enum class EWeaponRightType : uint8;
enum class EWeaponLeftType : uint8;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	NONE = 0,
	
	LEFT_WEAK = 1,
	RIGHT_WEAK = 2,

	LEFT_STRONG = 3,
	RIGHT_STRONG = 4,
};



UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();

public:
	UFUNCTION(BlueprintCallable)
	void CheckCombo();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void AttackRotation();

public:
	UFUNCTION()
	void RightWeak();

	UFUNCTION()
	void RightStrong();
	
	UFUNCTION()
	void LeftWeak();

	UFUNCTION()
	void LeftStrong();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float StaminaWeakAttack = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float StaminaStrongAttack = 20.f;
	
	UPROPERTY(EditDefaultsOnly)
	float RotationDuration =0.1f;
	
private:
	UPROPERTY(VisibleInstanceOnly)
	EWeaponRightType WeaponRight;
	
	UPROPERTY(VisibleInstanceOnly)
	EWeaponLeftType WeaponLeft;

private:
	UPROPERTY()
	UWeaponComponent* WeaponComponent;
	
	UPROPERTY()
	UAnimationComponent* AnimationComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;
	
	UPROPERTY()
	UStaminaComponent* StaminaComponent;
	
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	int Combo = 0;
	
	UPROPERTY()
	bool IsCombo = false;
	
private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void UpdateWeapon();
	
	UFUNCTION()
	void Attack(EAttackType AttackType);
	
	UFUNCTION()
	void Animation(EAttackType AttackType);

	UFUNCTION()
	void SwordAnimationWeak();
	
	UFUNCTION()
	void SwordAnimationStrong();
	
	UFUNCTION()
	void ResetCombo();

private:
	virtual void BeginPlay() override;
		
};
