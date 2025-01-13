#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JumpComponent.generated.h"


class UStateComponent;
class UAnimationComponent;
class UStaminaComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UJumpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJumpComponent();

public:
	UFUNCTION(BlueprintCallable)
	void End();
	
	UFUNCTION()
	void Try();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float Stamina = 10.f;
	
private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;
	
private:
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
	void Jump();

private:
	virtual void BeginPlay() override;
	
};
