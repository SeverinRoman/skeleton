#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeadComponent.generated.h"


class UStateComponent;
class UPhysicsHelperComponent;
class UInputCatcherComponent;
// class UAnimationComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UDeadComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDeadComponent();

public:
	UFUNCTION()
	void Dead();

private:
	UPROPERTY()
	AActor* Owner;

	UPROPERTY()
	bool IsDead = false;

private:
	UPROPERTY()
	UStateComponent* StateComponent;
	
	UPROPERTY()
	UPhysicsHelperComponent* PhysicsHelperComponent;
	
	UPROPERTY()
	UInputCatcherComponent* InputCatcherComponent;
	
	// UPROPERTY()
	// UAnimationComponent* AnimationComponent;

private:
	UFUNCTION()
	void Init();

private:
	virtual void BeginPlay() override;
};
