#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeComponent.generated.h"


class UAnimationComponent;
class UStateComponent;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDodgeComponent();

public:
	UFUNCTION(BlueprintCallable)
	void DodgeEnd();

public:
	UFUNCTION()
	void Dodge();

private:
	UPROPERTY()
	AActor* Owner;

private:
	UPROPERTY()
	UAnimationComponent* AnimationComponent;
	
	UPROPERTY()
	UStateComponent* StateComponent;

private:
	UFUNCTION()
	void Init();
	
	UFUNCTION()
	void DodgeStart();

protected:
	virtual void BeginPlay() override;
	
};
