#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsHelperComponent.generated.h"


class USkeletalMeshComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UPhysicsHelperComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPhysicsHelperComponent();

public:
	UFUNCTION(BlueprintCallable)
	void EnablePhysics();

private:
	UPROPERTY(EditDefaultsOnly)
	float PhysicsDelay = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	FName TagSkeletalMesh = "physics_skeletal_mesh";

	UPROPERTY(EditDefaultsOnly)
	FName TagStaticMesh = "physics_static_mesh";

private:
	UPROPERTY(VisibleInstanceOnly)
	TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
	
	UPROPERTY()
	TArray<UStaticMeshComponent*>  StaticMeshComponents;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	FTimerHandle PhysicsDelayTimerHandle;

private:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void InitSkeletalMesh();
	
	UFUNCTION()
	void InitStaticMesh();
	
	UFUNCTION()
	void SetLeaderPoseComponents(USkinnedMeshComponent* NewLeaderBoneComponent);

	UFUNCTION()
	void EnablePhysicsSkeletalMesh();
	
	UFUNCTION()
	void EnablePhysicsStaticMesh();

protected:
	virtual void BeginPlay() override;
};
