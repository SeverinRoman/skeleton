#pragma once

// #include "StandByAnimationType.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"


class USkeletalMeshComponent;

enum class EStandByAnimationType: uint8;
enum class EAnimationType: uint8;
enum class ELandingAnimationType: uint8;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAnimationComponent();

public:
	UFUNCTION(BlueprintCallable)
	void Play(UAnimMontage* AnimMontage);
	
	UFUNCTION(BlueprintCallable)
	void Pause();
	
	UFUNCTION(BlueprintCallable)
	void Stop(float Blend = 0.1f);

public:
	UFUNCTION()
	void PlayLanding(ELandingAnimationType AnimationLanding);
	
	UFUNCTION()
	void PlaySword(ESwordAnimationType StandByAnimation);
	
	UFUNCTION()
	void PlayStandBy(EStandByAnimationType StandByAnimation);

	UFUNCTION()
	void PlayBase(EAnimationType Animation);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<EAnimationType, UAnimMontage*> Animations;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EStandByAnimationType, UAnimMontage*> StandByAnimations;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ESwordAnimationType, UAnimMontage*> SwordAnimations;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ELandingAnimationType, UAnimMontage*> LandingAnimations;

	UPROPERTY(EditDefaultsOnly)
	FName TagSkeletalMesh = "skeletal_mesh";
	
private:
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	UAnimInstance* AnimInstance;

	UPROPERTY()
	TArray<UAnimInstance*> AnimInstances;

private:
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	
private:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void InitAnimInstances();
	
	UFUNCTION()
	void PlayAll(UAnimMontage* AnimMontage);
	
	UFUNCTION()
	void StopAll(float Blend);
	
	UFUNCTION()
	void PauseAll();
	
private:
	virtual void BeginPlay() override;
	
};
