#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkeletonCharacter.generated.h"


class UInputCatcherComponent;


UCLASS()
class SKELETON_API ASkeletonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkeletonCharacter();

private:
	UPROPERTY()
	UInputCatcherComponent* InputCatcherComponent;

private:
	UFUNCTION()
	void Init();
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
