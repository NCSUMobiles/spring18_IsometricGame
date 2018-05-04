// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Trigger.h"
#include "DraggableBlock.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class NINELIVES_ISOGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbookComponent* flipbookComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* fw_right_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* fw_left_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* bw_right_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* bw_left_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* fw_right_idle_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* fw_left_idle_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* bw_right_idle_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbook* bw_left_idle_Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = paper, meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* spriteComp;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* PlayerCameraBoom;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;


public:
	APlayerCharacter();

	// Called every frame;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float walkingSpeed;

	APlayerController* MyPC;
	AActor* clickedActor;
	//AActor* clickedBlock;
	//ADraggableBlock* clickedBlock;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void Jump();

	void StopJumping();

	void Interact();

	void StopInteracting();

	void MouseDown();

	void MouseUp();

	//True for fade in, false for fade out
	//Int for how many seconds you want the fade to be
	//True for if you want a delay afterwards, false if not
	//Int for how long you want said delay
	UFUNCTION(BlueprintImplementableEvent)
		void FadeCameraEffect(bool inOrOut, int fadeDuration, bool hasDelay, int delayDuration);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return PlayerCameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return PlayerCamera; }

	bool isInteracting;
	FRotator Rotation;

	UPROPERTY(BlueprintReadWrite)
		ATrigger* actionObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canMove;
};

