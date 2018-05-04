/**
	A PathFollower moves along a set of points and can be toggled on and off - it will stop on the grid if turned off
	A PathFollower takes in a set of points with coordinates and a speed
	@author Jacob Inkrote - Primary programmer
	@author Tony Mosolf - Primary programmer
	@author Jane Hiltz - Minor additions: Added trigger functionality
*/

#include "PathFollower.h"


// Sets default values
APathFollower::APathFollower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");

}

// Called when the game starts or when spawned
void APathFollower::BeginPlay()
{
	Super::BeginPlay();
	if (Locations.Num() > 0){
		changes = Locations[index] - GetActorLocation();
		changeVec = changes.GetSafeNormal(0.1f);
		changes = velocity * changeVec;
	}
	isFinishing = false;
	startLoc = GetActorLocation();
}

// Called every frame
void APathFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTriggered) {
		Activate();
		isTriggered = false;
	}

	if (isActive) {
		//UE_LOG(LogTemp, Warning, TEXT("in active tick"));
		if (travel()) {
			SetActorLocation(Locations[index], true);
			index += adjust;
			if (index >= Locations.Num()) {
				if (looping)
					index = 0;
				else {
					adjust *= -1;
					index -= 2;
				}
			}
			if (index < 0) {
				index = 1;
				adjust *= -1;
			}

			changes = Locations[index] - GetActorLocation();
			changeVec = changes.GetSafeNormal(0.1f);
			changes = velocity * changeVec;
		}
		if (isFinishing) {
			UE_LOG(LogTemp, Warning, TEXT("in is finishing tick"));
			FVector proxToPoint = (GetActorLocation() - startLoc);
			FVector proxToPointModded = FVector(((int)(proxToPoint.X + velocity)) % 100, ((int)(proxToPoint.Y + velocity)) % 100, ((int)(proxToPoint.Z + velocity)) % 100);
			//UE_LOG(LogTemp, Warning, TEXT("prox Vec : %f, %f, %f"), proxToPointModded.X, proxToPointModded.Y, proxToPointModded.Z);
			if (proxToPointModded.Size() < (2 * velocity)) {
				isActive = false;
				isFinishing = false;
			}
		}
	}

}

bool APathFollower::travel() {
	if (Locations.Num() > 0) {
		FVector goal = Locations[index];
		FVector loc = GetActorLocation();
		SetActorLocation(loc+changes, true);
		return FVector::Dist(GetActorLocation(), goal) < 2 * velocity;
	}
	return false;
}

int APathFollower::updateAxis(int current, int goal, int changeVal) {
	if (current == goal)
		return current;
	else if (current < goal) {
		if (current + changeVal >= goal)
			return goal;
		return current + changeVal;
	}
	else {
		if (current - changeVal <= goal)
			return goal;
		return current - changeVal;
	}
}

void APathFollower::Activate() {
		isActive = true;
}

void APathFollower::Deactivate() {
	if (canToggleAnywhere) {
		isActive = false;
	}
	else {
		isFinishing = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Loc in deactivate: %s"), *this->GetActorLocation().ToString());
	
}

