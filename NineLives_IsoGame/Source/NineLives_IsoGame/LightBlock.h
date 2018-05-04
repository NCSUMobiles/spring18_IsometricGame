// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightBlock.generated.h"

UCLASS()
class NINELIVES_ISOGAME_API ALightBlock : public AActor
{
	GENERATED_BODY()

		

	UPROPERTY(EditAnywhere)
		TArray<ALightBlock*> adjacent;
	
public:	
	// Sets default values for this actor's properties
	ALightBlock();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool lit;

	UFUNCTION(BlueprintCallable)
	void Change();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

	
};
