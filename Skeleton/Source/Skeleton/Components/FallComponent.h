#pragma once

#include "CoreMinimal.h"
#include "LandingAnimationType.h"
#include "Components/ActorComponent.h"
#include "FallComponent.generated.h"


class UStateComponent;
class UAnimationComponent;
class UHealthComponent;

enum class ELandingAnimationType : uint8;


USTRUCT(BlueprintType)
struct FLandingConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Speed = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.f;
	
	UPROPERTY(EditDefaultsOnly)
	ELandingAnimationType AnimationLanding = ELandingAnimationType::NONE;
	
};


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UFallComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFallComponent();

public:
	UFUNCTION(BlueprintCallable)
	void LandedEnd();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FLandingConfig> LandingConfigs;
	
	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY()
	UStateComponent* StateComponent;
	
	UPROPERTY()
	UAnimationComponent* AnimationComponent;
	
	UPROPERTY()
	UHealthComponent* HealthComponent;

private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	ACharacter* Character;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void OnLanded(const FHitResult& Hit);

private:
	virtual void BeginPlay() override;
		
};
