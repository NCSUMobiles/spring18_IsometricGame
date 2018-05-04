// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerableButton.h"
#include "Block.generated.h"

UCLASS()
class NINELIVES_ISOGAME_API ABlock : public ATriggerableButton
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate();

	void Deactivate();

	FVector starter;
	double counter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isActive;
	UPROPERTY(EditAnywhere)
		bool onlyRunOnce;
	UPROPERTY(EditAnywhere)
		bool doesRecycle;
	UPROPERTY(EditAnywhere)
		double change;
	UPROPERTY(EditAnywhere)
		int moveX;
	UPROPERTY(EditAnywhere)
		int moveY;
	UPROPERTY(EditAnywhere)
		int moveZ;

	void Movement();
	void AdjustMovement(int x, int y, int z, int value);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OneDMove(float&, float&, int&);
	void TwoDMove(float& location1, float &location2, float& start1, float &start2, int move1, int move2, FVector& location);

};
