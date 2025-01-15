#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RagdollComponent.generated.h"


class USkeletalMeshComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API URagdollComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URagdollComponent();

public:
	UFUNCTION(BlueprintCallable)
	void SetLeaderPoseComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	float PhysicsDelay = 0.1f;

private:
	UPROPERTY(VisibleInstanceOnly)
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
	
	UPROPERTY()
	TArray<UStaticMeshComponent*>  StaticMeshComponents;

private:
	UPROPERTY()
	UWorld* World;

private:
	UFUNCTION()
	void Init();

protected:
	virtual void BeginPlay() override;
};
