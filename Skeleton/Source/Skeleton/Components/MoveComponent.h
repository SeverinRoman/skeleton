#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


class UCharacterMovementComponent;
class UAnimationComponent;
class UStateComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMoveComponent();

public:
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = 450.f;

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
	void Run();

	UFUNCTION(BlueprintCallable)
	void Walk();

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

private:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
