#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


class UWeaponComponent;
class UAnimationComponent;
class UStateComponent;

enum class EWeaponRightType : uint8;
enum class EWeaponLeftType : uint8;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();

public:
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

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
	UPROPERTY()
	UWeaponComponent* WeaponComponent;
	
	UPROPERTY()
	UAnimationComponent* AnimationComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;
	
private:
	UPROPERTY(VisibleInstanceOnly)
	EWeaponRightType WeaponRight;


	UPROPERTY(VisibleInstanceOnly)
	EWeaponLeftType WeaponLeft;

private:
	UPROPERTY()
	int Combo = 0;
	
private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void UpdateWeapon();

private:
	virtual void BeginPlay() override;
		
};
