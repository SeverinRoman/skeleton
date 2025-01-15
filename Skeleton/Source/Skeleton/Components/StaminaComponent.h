#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaEnd);


class UStateComponent;
class UMoveComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();

public:
	UFUNCTION(BlueprintCallable)
	void Add(float Add);
	
	UFUNCTION(BlueprintCallable)
	void Sub(float Sub);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetStamina() { return CurrentStamina; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPercentStamina() { return CurrentStamina / MaxStamina; };
	
public:
	UFUNCTION()
	float GetIsStaminaOver() { return IsStaminaOver; };

public:
	UPROPERTY(BlueprintAssignable)
	FOnStaminaChange OnStaminaChange;
	
	UPROPERTY(BlueprintAssignable)
	FOnStaminaEnd OnStaminaEnd;

private:
	UPROPERTY(EditDefaultsOnly)
	float DelayRegeneration = 0.1f;

	float DelayOver = 2.f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxStamina = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float StartStamina = 100.f;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	UStateComponent* StateComponent;

	UPROPERTY()
	UMoveComponent* MoveComponent;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	FTimerHandle TimerHandleRegeneration;

	UPROPERTY()
	FTimerHandle TimerHandleOver;	
	
	UPROPERTY()
	float CurrentStamina;

	UPROPERTY()
	float IsStaminaOver = false;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void Over();
	
	UFUNCTION()
	void Regeneration();
	
	UFUNCTION()
	bool Deterioration();

private:	
	virtual void BeginPlay() override;
};
