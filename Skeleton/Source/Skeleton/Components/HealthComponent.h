#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class UDeadComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChange);



UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

public:
	UFUNCTION(BlueprintCallable)
	void Add(float Add);
	
	UFUNCTION(BlueprintCallable)
	void Sub(float Sub);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHealth() { return CurrentHealth; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPercentHealth() { return CurrentHealth / MaxHealth; };

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChange OnHealthChange;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float StartHealth = 50.f;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	UDeadComponent* DeadComponent;
	
	UPROPERTY()
	float CurrentHealth;

	UPROPERTY()
	float IsHealthOver = false;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void Over();
	
public:	
	virtual void BeginPlay() override;
		
};
