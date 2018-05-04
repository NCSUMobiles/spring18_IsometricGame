/**
	A WorldRotation triggerable object can be triggered to rotate objects in the game space
	It takes in the target, speed, and direction of the rotation
	@author Jacob Inkrote - Primary programmer

*/

#include "WorldRotationTriggerable.h"
#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Block.h"

char AWorldRotationTriggerable::currentRotation = 0;

void AWorldRotationTriggerable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!rotationRoot) {
		UE_LOG(LogTemp, Warning, TEXT("UNSET ROTATION ROOT"));
		return;
	}

	if (isTriggered) {
		UE_LOG(LogTemp, Warning, TEXT("Triggered tick"));
		if(!isActive){
			isActive = true;
			rotTicks = 120.0 / (rotSpeed*180/3.141592);
		}
		isTriggered = false;
	}
	if (isActive) {
		UE_LOG(LogTemp, Warning, TEXT("Rotating"));
		UE_LOG(LogTemp, Warning, TEXT("Rotation is %f %f %f"), rotationRoot->GetActorRotation().Roll, rotationRoot->GetActorRotation().Pitch, rotationRoot->GetActorRotation().Yaw);

		int negative = 1;

		switch (rotationDirection) {
		case Facing::UpRight:
			switch (AWorldRotationTriggerable::currentRotation) {
			case 0: negative = 1; break;
			case 1: negative = -1;  break;
			case 2: negative = 0;  break;
			}
			break;
		case Facing::UpLeft:
			switch (AWorldRotationTriggerable::currentRotation) {
			case 0: negative = -1; break;
			case 1: negative = 0;  break;
			case 2: negative = 1;  break;
			}
			break;
		case Facing::Forward:
			switch (AWorldRotationTriggerable::currentRotation) {
			case 0: negative = 0; break;
			case 1: negative = 1;  break;
			case 2: negative = -1;  break;
			}
			break;
		}

		UE_LOG(LogTemp, Warning, TEXT("neg is %d"), negative);
		UE_LOG(LogTemp, Warning, TEXT("facing is %d"), (int)rotationDirection);
		UE_LOG(LogTemp, Warning, TEXT("AWorldRotationTriggerable::currentRotation is %d"), AWorldRotationTriggerable::currentRotation);

		if (negative == 0) {
			rotTicks = 0;
			isActive = false;
		} else {
			FVector rotAxis(1.0, 1.0, -1.0);
			rotAxis.Normalize();
			rotationRoot->AddActorLocalRotation(FQuat(rotAxis, (negative)* rotSpeed));
			rotTicks--;
		}

		if (rotTicks <= 0) {
			isActive = false;
			currentRotation = (currentRotation + negative) % 3;
			currentRotation = currentRotation == -1 ? 2 : currentRotation;
			FRotator currentRot = rotationRoot->GetActorRotation();
			//round to nearest multiple of 45
			currentRot.Yaw = FMath::RoundToInt(currentRot.Yaw / 45) * 45;
			currentRot.Pitch = FMath::RoundToInt(currentRot.Pitch / 45) * 45;
			currentRot.Roll = FMath::RoundToInt(currentRot.Roll / 45) * 45;
			rotationRoot->SetActorRelativeRotation(FQuat(currentRot));
		}
	}
}

AWorldRotationTriggerable::AWorldRotationTriggerable() {
	PrimaryActorTick.bCanEverTick = true;
}


void AWorldRotationTriggerable::BeginPlay()
{
	// Call blueprints beginplay AFTER everything is setup
	Super::BeginPlay();

	AWorldRotationTriggerable::currentRotation = 0;
}
