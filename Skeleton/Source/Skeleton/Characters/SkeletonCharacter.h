#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkeletonCharacter.generated.h"


class UGameInputComponent;


UCLASS()
class SKELETON_API ASkeletonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkeletonCharacter();

private:
	UPROPERTY()
	UGameInputComponent* GameInputComponent;

private:
	UFUNCTION()
	void Init();
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
