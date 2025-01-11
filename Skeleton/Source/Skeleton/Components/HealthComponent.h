#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


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

	UFUNCTION(BlueprintCallable)
	float GetHealth() { return CurrentHealth; };

	UFUNCTION(BlueprintCallable)
	float GetPercentHealth() { return CurrentHealth / MaxHealth; };

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float StartHealth = 50.f;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
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
