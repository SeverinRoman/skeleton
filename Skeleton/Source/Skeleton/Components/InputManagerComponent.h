#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputManagerComponent.generated.h"


class UInputCatcherComponent;
class UDodgeComponent;
class UMoveComponent;
class ACharacter;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UInputManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputManagerComponent();

private:
	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

	UPROPERTY(EditDefaultsOnly)
	float DurationRun = 0.5f;

private:
	UPROPERTY()
	UWorld* World;
	
	UPROPERTY()
	AActor* Owner;
	
	UPROPERTY()
	FTimerHandle TimerHandleRun;
	
	UPROPERTY()
	bool IsSprint = false;
	
private:
	UPROPERTY()
	UInputCatcherComponent* InputCatcherComponent;
	
	UPROPERTY()
	UDodgeComponent* DodgeComponent;
	
	UPROPERTY()
	UMoveComponent* MoveComponent;
	
	UPROPERTY()
	ACharacter* Character;

private:
	UFUNCTION()
	void Init();

private:
	UFUNCTION()
	void OnInputMove(const FInputActionInstance InputActionInstance);

	UFUNCTION()
	void OnInputLook(const FInputActionInstance InputActionInstance);
	
	UFUNCTION()
	void OnInputDodgeRunJump(const FInputActionInstance InputActionInstance, const bool IsPressed);

private:
	virtual void BeginPlay() override;
		
};
