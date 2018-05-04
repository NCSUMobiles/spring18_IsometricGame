/**
	A Trigger object is the parent class to all triggerable objects
	It allows the player to interact with objects while they are inside a trigger box bounds
	@author Jane Hiltz - Primary programmer

*/

#include "Trigger.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"


APlayerCharacter *player;

// Sets default values
ATrigger::ATrigger() : canOverlap(true), isTriggered(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	triggerBox = CreateDefaultSubobject<UBoxComponent>("InteractableBox");
	OnActorBeginOverlap.AddDynamic(this, &ATrigger::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATrigger::OverlapEnd);
	triggerBox->bGenerateOverlapEvents = true;
	
}

//What happens when something interacts with the trigger box
void ATrigger::Trigger() {
	if (player != nullptr) {
		isTriggered = true;
		UE_LOG(LogTemp, Warning, TEXT("in Triggered()"));
	}
}

//Gives player trigger
void ATrigger::OverlapBegin(AActor* self, AActor* OtherActor) {
	//turns colided actor into a pawn
	APlayerCharacter* currentPlayer = Cast<APlayerCharacter>(OtherActor);
	player = currentPlayer;
	if (currentPlayer != nullptr && canOverlap /*&& !isTriggered*/) {
		currentPlayer->actionObj = this;
		UE_LOG(LogTemp, Warning, TEXT("in OverlapBegin()"));
		canOverlap = false;
	}
}

void ATrigger::OverlapEnd(AActor* self, AActor* OtherActor) {
	APlayerCharacter* currentPlayer = Cast<APlayerCharacter>(OtherActor);
	if (currentPlayer != nullptr && !canOverlap /*&& !isTriggered*/) {
		if (currentPlayer->actionObj == this) {
			currentPlayer->actionObj = nullptr;
		}
		UE_LOG(LogTemp, Warning, TEXT("in OverlapEnd()"));
		canOverlap = true;
	}
}


