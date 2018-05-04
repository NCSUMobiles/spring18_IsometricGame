// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DraggableBlock.generated.h"


UCLASS()
class NINELIVES_ISOGAME_API ADraggableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADraggableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	 
	bool isClicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isOverlapping;

	UPROPERTY(EditAnywhere)
	bool isMovable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isSpecial;

	float XCoord;

	float YCoord;

	float ZCoord;

	void OnClicked();

	void OnReleased();

	void SnapToGrid();

	void CheckSurrounding();

	//UFUNCTION()
	//void OverlapBegin(AActor* self, AActor* OtherActor);

	//UFUNCTION()
	//void OverlapEnd(AActor* self, AActor* OtherActor);
	
};
