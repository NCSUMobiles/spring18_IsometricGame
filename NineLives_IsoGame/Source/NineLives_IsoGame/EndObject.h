// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndObject.generated.h"

UCLASS()
class NINELIVES_ISOGAME_API AEndObject : public AActor
{
	GENERATED_BODY()

		
	
public:	
	// Sets default values for this actor's properties
	AEndObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;


	
};
