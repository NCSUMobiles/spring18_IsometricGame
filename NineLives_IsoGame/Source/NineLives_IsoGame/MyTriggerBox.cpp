/**
	A Trigger box is an object that the player can interact with and trigger other triggerable objects
	@author Jane Hiltz - Primary programmer
*/

#include "MyTriggerBox.h"
#include "DrawDebugHelpers.h"

AMyTriggerBox::AMyTriggerBox() {
	
	//OnOverlapBegin->AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
	//OnOverlapEnd->AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

void AMyTriggerBox::BeginPlay() {
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AMyTriggerBox::OnOverlapBegin(class AActor* OverlappingActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		//print("Overlap Begin");
		//printFString("Overlapped Actor = %s", *OverlappingActor->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
		UE_LOG(LogTemp, Warning, TEXT("Overlapped Actor = %s"), *OverlappingActor->GetName());
	}
}

void AMyTriggerBox::OnOverlapEnd(class AActor* OverlappingActor, class AActor* OtherActor) {
	if (OtherActor && (OtherActor != this)) {
		//print("Overlap Begin");
		//printFString("Overlapped Actor = %s", *OverlappingActor->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Overlap has Ended"));
		UE_LOG(LogTemp, Warning, TEXT("Overlapped Actor = %s"), *OtherActor->GetName());
	}
}


