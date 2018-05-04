// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.h"
#include "TriggerableButton.generated.h"

UENUM(BlueprintType)
enum class ButtonType : uint8 {
	Activate UMETA(DisplayName = "Activate"),
	Destroy UMETA(DisplayName = "Destroy"),
	Trigger UMETA(DisplayName = "Trigger")
};

/**
 * 
 */
UCLASS()
class NINELIVES_ISOGAME_API ATriggerableButton : public ATrigger
{
	GENERATED_BODY()

public:

	ATriggerableButton();

	UPROPERTY(EditAnywhere)
	AActor * triggeredActor;

	UPROPERTY(EditAnywhere)
		ButtonType buttonType;

	UPROPERTY(EditAnywhere)
		bool canToggle;

	UFUNCTION(BlueprintCallable)
		virtual void Trigger() override;

	bool isTriggered;

private:

	void Activate();

	void Destroy();

};
