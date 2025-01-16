#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


class UCharacterMovementComponent;
class UAnimationComponent;
class UStateComponent;
class UStaminaComponent;


UENUM(BlueprintType)
enum class EMoveType : uint8
{
	NONE = 0,

	WALK = 1,
	RUN = 2,
	SPRINT = 3,
};


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMoveComponent();

public:
	UFUNCTION()
	void ToggleRotation(bool bIsRotation);
	
	UFUNCTION()
	EMoveType GetMove() { return CurrentMove; };

public:
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 207.113632f;

	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = 516.988098f;

	UPROPERTY(EditDefaultsOnly)
	float SprintSpeed = 724.596985f;

public:
	UFUNCTION(BlueprintCallable)
	void Move(float X, float Y);

	UFUNCTION(BlueprintCallable)
	void Sprint();
	
	UFUNCTION(BlueprintCallable)
	void Run();

	UFUNCTION(BlueprintCallable)
	void Walk();

private:
	UPROPERTY(EditDefaultsOnly)
	EMoveType StartMove;

private:
	UPROPERTY(VisibleInstanceOnly)
	EMoveType CurrentMove;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;
	
	UPROPERTY()
	bool IsEnableRotation = true;
	
	UPROPERTY()
	FRotator SaveRotationRate;

private:
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;

	UPROPERTY()
	UAnimationComponent* AnimationComponent;
	
	UPROPERTY()
	UStaminaComponent* StaminaComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void StopStandBy();

private:
	UFUNCTION()
	void OnStaminaEnd();
	
	UFUNCTION()
	void StopAnimation();

private:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
