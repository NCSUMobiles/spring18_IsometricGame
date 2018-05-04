/**
	A Draggable Block is an object that can be dragged by the players mouse to a certain location, given it is not colliding with another draggable block, and snap to the grid
	A Draggable Block can be unmovable and special 
	@author Jane Hiltz
*/

#include "DraggableBlock.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"


FVector startPos;
FVector prevPos;
FVector newLoc;
FVector checkLoc;
float Scale;

// Sets default values
ADraggableBlock::ADraggableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//OnActorBeginOverlap.AddDynamic(this, &ADraggableBlock::OverlapBegin);
	//OnActorEndOverlap.AddDynamic(this, &ADraggableBlock::OverlapEnd);

	// Set as root component
	//RootComponent = MyComp;

}

// Called when the game starts or when spawned
void ADraggableBlock::BeginPlay()
{
	isClicked = false; 
	isOverlapping = false;

	Super::BeginPlay();

	startPos = GetActorLocation();
	
	XCoord = startPos.X;
	YCoord = startPos.Y;
	ZCoord = startPos.Z;
	
}

// Called every frame
void ADraggableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isClicked && isMovable) {
		newLoc = FVector(XCoord, YCoord, ZCoord);
		//UE_LOG(LogTemp, Warning, TEXT("Block Loc pre Snap: %s"), *this->GetActorLocation().ToString());
		//SnapToGrid();
		SetActorRelativeLocation(newLoc);
	}
}

void ADraggableBlock::OnClicked() {
//	UE_LOG(LogTemp, Warning, TEXT("In OnClicked"));
//	UE_LOG(LogTemp, Warning, TEXT("draggable actors name: %s"), *this->GetName());
	if (isMovable) {
		prevPos = GetActorLocation();
		isClicked = true;
	}
}

void ADraggableBlock::OnReleased() {
//	UE_LOG(LogTemp, Warning, TEXT("In OnReleased"));
	if (isMovable) {
		SnapToGrid();
		SetActorLocation(newLoc);
		if (isOverlapping) {
			UE_LOG(LogTemp, Warning, TEXT("is overlapping"));
			CheckSurrounding();
		}
		UE_LOG(LogTemp, Warning, TEXT("Block Loc post Snap: %s"), *this->GetActorLocation().ToString());
		prevPos = newLoc;
		isClicked = false;
	}
}

void ADraggableBlock::SnapToGrid() {
	FVector diff = newLoc - prevPos;
	newLoc = FVector(floor(newLoc.X / 100) * 100, floor(newLoc.Y / 100) * 100, floor(newLoc.Z / 100) * 100);
}

void ADraggableBlock::CheckSurrounding() {
	checkLoc = FVector(newLoc.X - 100, newLoc.Y, newLoc.Z);
	SetActorLocation(checkLoc);
	UE_LOG(LogTemp, Warning, TEXT("check 1"));
	if (isOverlapping) {
		checkLoc = FVector(newLoc.X, newLoc.Y - 100, newLoc.Z);
		SetActorLocation(checkLoc);
		UE_LOG(LogTemp, Warning, TEXT("check 2"));
	}
	if (isOverlapping) {
		checkLoc = FVector(newLoc.X - 100, newLoc.Y - 100, newLoc.Z);
		SetActorLocation(checkLoc);
		UE_LOG(LogTemp, Warning, TEXT("check 3"));
	}
	if (isOverlapping) {
		checkLoc = FVector(newLoc.X + 100, newLoc.Y, newLoc.Z);
		SetActorLocation(checkLoc);
		UE_LOG(LogTemp, Warning, TEXT("check 4"));
	}
	if (isOverlapping) {
		checkLoc = FVector(newLoc.X, newLoc.Y + 100, newLoc.Z);
		SetActorLocation(checkLoc);
		UE_LOG(LogTemp, Warning, TEXT("check 5"));
	}
	if (isOverlapping) {
		checkLoc = FVector(newLoc.X + 100, newLoc.Y + 100, newLoc.Z);
		SetActorLocation(checkLoc);
		UE_LOG(LogTemp, Warning, TEXT("check 6"));
	}
	if (isOverlapping) {
		SetActorLocation(prevPos);
		UE_LOG(LogTemp, Warning, TEXT("check 7 - FINAL"));
	}
}

//void ADraggableBlock::OverlapBegin(AActor* self, AActor* OtherActor) {
//	UE_LOG(LogTemp, Warning, TEXT("in OverlapBegin() 1"));
//	//APlayerCharacter* currentPlayer = Cast<APlayerCharacter>(OtherActor);
//	//player = currentPlayer;
//	
//	if (OtherActor != nullptr && canOverlap) {
//		//currentPlayer->actionObj = this;
//		UE_LOG(LogTemp, Warning, TEXT("in OverlapBegin()"));
//		canOverlap = false;
//	}
//}
//
//void ADraggableBlock::OverlapEnd(AActor* self, AActor* OtherActor) {
//	UE_LOG(LogTemp, Warning, TEXT("in OverlapEnd() 1"));
//	//APlayerCharacter* currentPlayer = Cast<APlayerCharacter>(OtherActor);
//	if (OtherActor != nullptr && !canOverlap /*&& !isTriggered*/) {
//		//if (currentPlayer->actionObj == this) {
//		//	currentPlayer->actionObj = nullptr;
//		//}
//		UE_LOG(LogTemp, Warning, TEXT("in OverlapEnd()"));
//		canOverlap = true;
//	}
//}
