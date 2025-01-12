#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaChange);


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
	UPROPERTY(BlueprintAssignable)
	FOnStaminaChange OnStaminaChange;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxStamina = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float StartStamina = 100.f;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	float CurrentStamina;

	UPROPERTY()
	float IsStaminaOver = false;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void Over();


private:	
	virtual void BeginPlay() override;
};
