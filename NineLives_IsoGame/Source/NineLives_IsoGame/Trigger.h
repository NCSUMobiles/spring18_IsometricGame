// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Trigger.generated.h"

UCLASS()
class NINELIVES_ISOGAME_API ATrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrigger();

protected:

	UPROPERTY(EditAnywhere)
	bool oneTime = true;

	UPROPERTY(EditAnywhere)
	UBoxComponent* triggerBox;
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	bool canOverlap;
	bool isTriggered;

	UFUNCTION(BlueprintCallable, Category = "Button Trigger")
		virtual void Trigger();

	UFUNCTION()
		void OverlapBegin(AActor* self, AActor* OtherActor);

	UFUNCTION()
		void OverlapEnd(AActor* self, AActor* OtherActor);

};
