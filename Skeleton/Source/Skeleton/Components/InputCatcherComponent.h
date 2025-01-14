#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "InputCatcherComponent.generated.h"


class UEnhancedInputComponent;
class APlayerController;
class AController;
class UInputAction;
class UInputMappingContext;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMove, FInputActionInstance, InputActionInstance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputLook, FInputActionInstance, InputActionInstance);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputDodgeRunJump, FInputActionInstance, InputActionInstance, bool, IsPressed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputRightAttackWeak, FInputActionInstance, InputActionInstance, bool, IsPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInputRightAttackStrong, FInputActionInstance, InputActionInstance, bool, IsPressed);


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKELETON_API UInputCatcherComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputCatcherComponent();

public:
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	UPROPERTY(BlueprintAssignable)
	FOnInputMove OnInputMove;
	
	UPROPERTY(BlueprintAssignable)
	FOnInputLook OnInputLook;
	
	UPROPERTY(BlueprintAssignable)
	FOnInputDodgeRunJump OnInputDodgeRunJump;
	
	UPROPERTY(BlueprintAssignable)
	FOnInputRightAttackWeak OnInputRightAttackWeak;

	UPROPERTY(BlueprintAssignable)
	FOnInputRightAttackStrong OnInputRightAttackStrong;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly)
	int PlayerNum = 0;

	UPROPERTY(EditDefaultsOnly)
	bool IsDebug = false;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* DodgeRunJumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* WeakAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UInputAction* StrongAttackAction;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	AController* Controller;

private:
	UFUNCTION()
	void BindInputs();

private:
	UFUNCTION()
	void OnInputMoveStarted(const FInputActionInstance& InputActionInstance) { OnInputMove.Broadcast(InputActionInstance);};
	
	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionInstance& InputActionInstance) { OnInputMove.Broadcast(InputActionInstance);};

	UFUNCTION()
	void OnInputMoveCompleted(const FInputActionInstance& InputActionInstance) { OnInputMove.Broadcast(InputActionInstance);};

	
	UFUNCTION()
	void OnInputLookStarted(const FInputActionInstance& InputActionInstance) { OnInputLook.Broadcast(InputActionInstance);};
	
	UFUNCTION()
	void OnInputLookTriggered(const FInputActionInstance& InputActionInstance) { OnInputLook.Broadcast(InputActionInstance);};

	UFUNCTION()
	void OnInputLookCompleted(const FInputActionInstance& InputActionInstance) { OnInputLook.Broadcast(InputActionInstance);};

	
	UFUNCTION()
	void OnInputDodgeRunJumpStarted(const FInputActionInstance& InputActionInstance) { OnInputDodgeRunJump.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputDodgeRunJumpCompleted(const FInputActionInstance& InputActionInstance) { OnInputDodgeRunJump.Broadcast(InputActionInstance, false);};


	UFUNCTION()
	void OnInputAttackWeakStarted(const FInputActionInstance& InputActionInstance) { OnInputRightAttackWeak.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputAttackWeakCompleted(const FInputActionInstance& InputActionInstance) { OnInputRightAttackWeak.Broadcast(InputActionInstance, false);};


	UFUNCTION()
	void OnInputAttackStrongStarted(const FInputActionInstance& InputActionInstance) { OnInputRightAttackStrong.Broadcast(InputActionInstance, true);};
	
	UFUNCTION()
	void OnInputAttackStrongCompleted(const FInputActionInstance& InputActionInstance) { OnInputRightAttackStrong.Broadcast(InputActionInstance, false);};
	
private:
	virtual void BeginPlay() override;
	
};
