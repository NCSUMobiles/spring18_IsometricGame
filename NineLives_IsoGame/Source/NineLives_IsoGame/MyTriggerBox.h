// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class NINELIVES_ISOGAME_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	AMyTriggerBox();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappingActor, class AActor* OtherActor);
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappingActor, class AActor* OtherActor);
	
	
	
};
