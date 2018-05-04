/**
	A Block moves in that direction with that speed and either stops, loops, or recycles
	A Block object takes in a speed (counter) and a direction in one or more planes (x, y, z)
	@author Tony Mosolf - Primary programmer
	@author Jacob Inkrote - Primary programmer
	@author Jane Hiltz - Minor additions: Added trigger, not looping, and recycling functionality
*/

#include "Block.h"
#include <cmath>

bool backToBeginning;

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Stores the original spawn location
	//starter = GetActorLocation();
	
	//Counter used to figure out what tick is being done
	counter = 0;
	//Change value used to indicate positive or negative movement
	//change = 10;
	//The value to be moved on the x-axis
	//moveX = 500;
	//The value to be moved on the y-axis
	//moveY = 0;
	//The value to be moved on the z-axis
	//moveZ = 0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");
	//Mesh->AttachParent = RootComponent;
}

//Typedef for a function pointer that takes no operators and returns void

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	starter = GetActorLocation();
	backToBeginning = false;
	//UE_LOG(LogTemp, Warning, TEXT("Starter in begin: %s"), *starter.ToString());
	//AdjustMovement(100, 100, 0, .05);
	
}

void ABlock::AdjustMovement(int x, int y, int z, int value) {
	moveX = x;
	moveY = y;
	moveZ = z;
	counter = 0;
	change = value;
	SetActorLocation(starter);
}


//Symmetrical movement across origins around start
//Either back and forth or circular motion
void ABlock::Movement() {
	FVector moving = GetActorLocation();
	if (moveX*moveY > 0) {
		TwoDMove(moving.X, moving.Y, starter.X, starter.Y, moveX, moveY, moving);
	}
	else if (moveX*moveZ > 0) {
		TwoDMove(moving.X, moving.Z, starter.X, starter.Z, moveX, moveZ, moving);
	}
	else if (moveZ*moveY > 0) {
		TwoDMove(moving.Z, moving.Y, starter.Z, starter.Y, moveZ, moveY, moving);
	}
	else if (moveX > 0) {
		OneDMove(moving.X, starter.X, moveX);
	}
	else if (moveY > 0) {
		OneDMove(moving.Y, starter.Y, moveY);
	}
	else if (moveZ > 0) {
		OneDMove(moving.Z, starter.Z, moveZ);
	}

	if (backToBeginning) {
		SetActorLocation(starter, true);
		backToBeginning = false;
	}
	else {
		SetActorLocation(moving, true);
	}
	
}

void ABlock::OneDMove(float& location, float& start, int& move) {
	if (location > start + move || location < start - move) {
		if (onlyRunOnce) {
			isActive = false;
		}
		if (doesRecycle) {
			backToBeginning = true;
		}
		else {
			change *= -1;
		}
	}
	location += change;

}

void ABlock::TwoDMove(float& location1, float &location2, float& start1, float &start2, int move1, int move2, FVector& location) {
	location1 = start1 + cos(counter)*move1;
	location2 = start2 + sin(counter)*move2;
	if (SetActorLocation(location, true))
		counter += change;
	if (counter >= 2 * PI)
		counter -= 2 * PI;


}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTriggered) {
		Activate();
		isTriggered = false;
	}


	if (isActive) {
		Movement();
	}
}

void ABlock::Activate() {
	isActive = true;
	UE_LOG(LogTemp, Warning, TEXT("activating block"));
}

void ABlock::Deactivate() {
	isActive = false;
	UE_LOG(LogTemp, Warning, TEXT("deactivating block"));
}
