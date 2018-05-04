// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerableButton.h"
#include "PathFollower.generated.h"

UCLASS()
class NINELIVES_ISOGAME_API APathFollower : public ATriggerableButton
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	APathFollower();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isActive;
	UPROPERTY(EditAnywhere)
		bool canToggleAnywhere;
	bool isFinishing;
	UPROPERTY(EditAnywhere)
		TArray<FVector> Locations;
	int index = 0;

		FVector changes;

		FVector changeVec;

	int adjust = 1;

	UPROPERTY(EditAnywhere)
		bool looping;

	UPROPERTY(EditAnywhere)
		double velocity;

	void Activate();

	void Deactivate();

	bool travel();

	int updateAxis(int current, int goal, int changeVal);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	FVector startLoc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
