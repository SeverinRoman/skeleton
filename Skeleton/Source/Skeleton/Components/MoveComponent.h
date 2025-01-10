#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


class UCharacterMovementComponent;
class UAnimationComponent;
class UStateComponent;


UENUM(BlueprintType)
enum class EStartMoveType : uint8
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
	void Crouch();
	
	UFUNCTION(BlueprintCallable)
	void UnCrouch();
	
	UFUNCTION(BlueprintCallable)
	void Jump();
	
	UFUNCTION(BlueprintCallable)
	void UnJump();

	UFUNCTION(BlueprintCallable)
	void Sprint();
	
	UFUNCTION(BlueprintCallable)
	void Run();

	UFUNCTION(BlueprintCallable)
	void Walk();

private:
	UPROPERTY(EditDefaultsOnly)
	EStartMoveType StartMoveType;

private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;

private:
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;

	UPROPERTY()
	UAnimationComponent* AnimationComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void StopStandBy();
	
	UFUNCTION()
	void StartMove();

private:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
