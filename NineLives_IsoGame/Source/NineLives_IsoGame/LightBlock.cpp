/**
	A block that lights up and can turn on/off certain blocks around it
	@author Tony Mosolf - Primary programmer
*/

#include "LightBlock.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"


// Sets default values
ALightBlock::ALightBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	lit = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");



}

// Called when the game starts or when spawned
void ALightBlock::BeginPlay()
{
	Super::BeginPlay();
	adjacent.Empty();
	for (TActorIterator<ALightBlock> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ALightBlock *current = *ActorItr;
		if (FVector::Dist(GetActorLocation(), current->GetActorLocation()) < 125) {
			adjacent.Add(current);
		}
	}
	
}

// Called every frame
void ALightBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALightBlock::Change()
{
	for (ALightBlock* a : adjacent) {
		a->lit = !a->lit;
	}

}





