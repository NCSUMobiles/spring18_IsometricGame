// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "TriggerableButton.h"
#include "WorldRotationTriggerable.generated.h"

UENUM(BlueprintType)
enum class Facing : uint8 {
	UpRight UMETA(DisplayName = "Up and Right"),
	UpLeft UMETA(DisplayName = "Up and Left"),
	Forward UMETA(DisplayName = "Forward")
};

/**
 * 
 */
UCLASS()
class NINELIVES_ISOGAME_API AWorldRotationTriggerable : public ATriggerableButton
{

	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
	AActor * rotationRoot;

	UPROPERTY(EditAnywhere)
	APlayerCharacter * player;

	AWorldRotationTriggerable();

	UPROPERTY(EditAnywhere)
	Facing rotationDirection;

	UPROPERTY(EditAnywhere)
	float rotSpeed = 0.01;
	
	virtual void Tick(float DeltaTime) override;

	static char currentRotation;

private:
	
	bool isActive;

	int rotTicks;

protected:

	virtual void BeginPlay() override;

};
