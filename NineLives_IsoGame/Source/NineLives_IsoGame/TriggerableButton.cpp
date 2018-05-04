/**
	A Triggerable Button is an object that the player can interact with that can trigger other triggerable objects
	It takes in a target object to trigger and an action to perform with the trigger (activate, deactivate, destroy)
	@author Jane Hiltz - Primary programmer
*/

#include "TriggerableButton.h"
#include "PlayerCharacter.h"
#include "Block.h"
#include "PathFollower.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"

ATriggerableButton::ATriggerableButton() {
	PrimaryActorTick.bCanEverTick = false;
}

//called by player when interacting with objects
void ATriggerableButton::Trigger() {
	if (!isTriggered || canToggle) {

		Super::Trigger();

		isTriggered = !isTriggered;

		UE_LOG(LogTemp, Warning, TEXT("in TButton Trigger()"));

		switch (buttonType) {
		case ButtonType::Activate:
			Activate();
			break;
		case ButtonType::Destroy:
			Destroy();
			break;
		case ButtonType::Trigger:
			ATriggerableButton* target = Cast<ATriggerableButton>(triggeredActor);
			if (target != nullptr) { 
				target->isTriggered = true;
			}
			break;
		}

		//this is where we can mess with changing meshes
	}
}

void ATriggerableButton::Activate() {
	ABlock* block = Cast<ABlock>(triggeredActor);
	if (block != nullptr) {
		//block->isActive = !(block->isActive);
		if (block->isActive) {
			block->Deactivate();
		}
		else {
			block->Activate();
		}
	}

	APathFollower* pFollower = Cast<APathFollower>(triggeredActor);
	if (pFollower != nullptr) {
		//pFollower->isActive = !(pFollower->isActive);
		if (pFollower->isActive) {
			pFollower->Deactivate();
		}
		else {
			pFollower->Activate();
		}
	}
}

void ATriggerableButton::Destroy() {
	if (triggeredActor != nullptr) {
		triggeredActor->Destroy();
	}
}
