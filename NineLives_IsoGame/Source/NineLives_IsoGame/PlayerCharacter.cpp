/**
	This is the code that denotes the behavior for the player character and the camera
	@author Jane Hiltz - Pirmary programmer 
	@author Tony Mosolf - Minor additions: set up idle animation 
	@author Jacob Inkrote - Minor additions: added some rotation functionality 
*/

#include "PlayerCharacter.h"
#include <cmath>
//#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "DraggableBlock.h"
#include "GameFramework/PlayerController.h"

const int STEP_TIMER_AMOUNT = 60;

int interactingCounter;
bool isLeft;
bool isBackwards;
bool isIdle;
bool useMouse;
int stepTimer;
int idleCounter;
float mouseX;
float mouseY;

ADraggableBlock* clickedBlock;

FVector worldPos;
FVector worldRot;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	isInteracting = false;
	interactingCounter = -1;

	useMouse = false;

	isLeft = false;
	isBackwards = false;
	stepTimer = STEP_TIMER_AMOUNT;
	isIdle = true;
	idleCounter = 0;

	canMove = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//MyPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//MyPC->bEnableClickEvents = false;
	//MyPC->bShowMouseCursor = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->SetupAttachment(RootComponent);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f); // ...at this rotation rate
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->bCanWalkOffLedges = false;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PlayerCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	PlayerCameraBoom->SetupAttachment(RootComponent);
	PlayerCameraBoom->SetRelativeLocationAndRotation(FVector(300.0f, 300.0f, 25.0f), FRotator(-35.264f, 45.0f, 0.0f));
	PlayerCameraBoom->TargetArmLength = 300.0f;
	PlayerCameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	PlayerCamera->SetupAttachment(PlayerCameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	PlayerCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	PlayerCamera->SetOrthoWidth(2048.0f);

	fw_right_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_FW_R.peanut_FW_R'"), NULL, LOAD_None, NULL);
	fw_left_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_FW_L.peanut_FW_L'"), NULL, LOAD_None, NULL);
	bw_right_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_BW_R.peanut_BW_R'"), NULL, LOAD_None, NULL);
	bw_left_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_BW_L.peanut_BW_L'"), NULL, LOAD_None, NULL);

	fw_right_idle_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_FW_R_Idle.peanut_FW_R_Idle'"), NULL, LOAD_None, NULL);
	fw_left_idle_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_FW_L_Idle.peanut_FW_L_Idle'"), NULL, LOAD_None, NULL);
	bw_right_idle_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_BW_R_Idle.peanut_BW_R_Idle'"), NULL, LOAD_None, NULL);
	bw_left_idle_Flipbook = LoadObject<UPaperFlipbook>(NULL, TEXT("PaperFlipbook'/Game/Sprites/Peanut/peanut_BW_L_Idle.peanut_BW_L_Idle'"), NULL, LOAD_None, NULL);

	flipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbook"));
	flipbookComp->SetupAttachment(GetCapsuleComponent());

	actionObj = nullptr;
	flipbookComp->bGenerateOverlapEvents = true;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APlayerCharacter::StopInteracting);

	PlayerInputComponent->BindAction("MouseDown", IE_Pressed, this, &APlayerCharacter::MouseDown);
	PlayerInputComponent->BindAction("MouseDown", IE_Released, this, &APlayerCharacter::MouseUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::BeginPlay()
{
	//Fade in
	FadeCameraEffect(false, 5, false, 0);

	canMove = true;

	// Call blueprints beginplay AFTER everything is setup
	Super::BeginPlay();

	MyPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//ADraggableBlock* clickedBlock = Cast<ADraggableBlock>(clickedBlock);

	if (GetWorld()->GetName() == "DragAndDropTestMap" || GetWorld()->GetName() == "Geb_Lvl_1" || GetWorld()->GetName() == "Geb_Lvl_2" || GetWorld()->GetName() == "Geb_Lvl_3") {
		useMouse = true;
	}
	else {
		useMouse = false;
	}

	if (MyPC != nullptr){
		if (useMouse) {
			MyPC->bEnableClickEvents = true;
			MyPC->bShowMouseCursor = true;
		}
		else {
			MyPC->bEnableClickEvents = false;
			MyPC->bShowMouseCursor = false;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("pc is null"));
	}

	//Fade in
	FadeCameraEffect(false, 5, false, 0);
	UE_LOG(LogTemp, Warning, TEXT("past fade"));
	Rotation = Controller->GetControlRotation();

}

void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PLAYER LOCAION: %s"), *this->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("ROOT LOCAION: %s"), *this->GetRootComponent()->GetComponentLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("MESH LOCAION: %s"), *this->GetCapsuleComponent()->GetComponentLocation().ToString());
	if (interactingCounter > 0) {
		interactingCounter--;
	}
	else if (interactingCounter == 0) {
		isInteracting = false;
		interactingCounter = -1;
	}

	if (useMouse) {

		if (clickedBlock != nullptr) {
			MyPC->GetMousePosition(mouseX, mouseY);
			
			MyPC->DeprojectMousePositionToWorld(worldPos, worldRot);

			if (MyPC != nullptr) {
				FHitResult Hit;
				MyPC->GetHitResultUnderCursor(ECC_Pawn, false, Hit);
				if (Hit.bBlockingHit) {
					if (Hit.Actor != NULL) {
						FVector hitpoint = Hit.ImpactPoint;
						clickedBlock->XCoord = hitpoint.X;
						clickedBlock->YCoord = hitpoint.Y;
					}
				}
			}
			/*clickedBlock->XCoord = -mouseX;
			clickedBlock->YCoord = mouseY;*/
			//UE_LOG(LogTemp, Warning, TEXT("worldpos Loc: %s"), *worldPos.ToString());
			//UE_LOG(LogTemp, Warning, TEXT("mouse to world Loc: X= %f Y= %f"), mouseX, mouseY);
		}
	}
	isIdle = GetVelocity().IsZero();

	if (isIdle) {
		if (isBackwards) {
			if (isLeft) {
				flipbookComp->SetFlipbook(bw_left_idle_Flipbook);
			}
			else {
				flipbookComp->SetFlipbook(bw_right_idle_Flipbook);
			}
		}
		else {
			if (isLeft) {
				flipbookComp->SetFlipbook(fw_left_idle_Flipbook);
			}
			else {
				flipbookComp->SetFlipbook(fw_right_idle_Flipbook);
			}
		}
		
	}

}

void APlayerCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && canMove)
	{
		if (value > 0.0) {
			if (isBackwards) {
				flipbookComp->SetFlipbook(bw_right_Flipbook);
			}
			else {
				flipbookComp->SetFlipbook(fw_right_Flipbook);
			}
			isLeft = false;
		}
		else {
			if (isBackwards) {
				flipbookComp->SetFlipbook(bw_left_Flipbook);
			}
			else {
				flipbookComp->SetFlipbook(fw_left_Flipbook);
			}
			isLeft = true;
			isIdle = false;
		}

	    Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//FVector movement = Direction * (value * walkingSpeed);
		//FVector movement = value * walkingSpeed;
		AddMovementInput(Direction, value);
		//(GetActorLocation() + movement);
		//UE_LOG(LogTemp, Warning, TEXT("forward"));
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && canMove)
	{
		if (value > 0.0f) {
			if (isLeft) {
				flipbookComp->SetFlipbook(bw_left_Flipbook);
			}
			else {
				flipbookComp->SetFlipbook(bw_right_Flipbook);
			}
			isBackwards = true;
		}
		else if (value < 0.0f) {
			if (isLeft) {
				flipbookComp->SetFlipbook(fw_left_Flipbook);
			}
			else {
				flipbookComp->SetFlipbook(fw_right_Flipbook);
			}
			isBackwards = false;
			isIdle = false;
		}

		Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		FVector movement = Direction * (value * walkingSpeed);
		AddMovementInput(Direction, value);
		//SetActorLocation(GetActorLocation() + movement);
		//UE_LOG(LogTemp, Warning, TEXT("forward"));
	}

}

void APlayerCharacter::Jump()
{
	if (canMove) {
		ACharacter::Jump();
	}


}

void APlayerCharacter::StopJumping()
{
	if (canMove) {
		ACharacter::StopJumping();
	}

}

void APlayerCharacter::Interact()
{
	if (canMove) {
		isInteracting = true;
		interactingCounter = 1;

		if (actionObj != nullptr) {
			actionObj->Trigger();
		}
		UE_LOG(LogTemp, Warning, TEXT("in interact"));
	}
}

void APlayerCharacter::StopInteracting()
{
	if (canMove) {
		isInteracting = false;
	}
}

void APlayerCharacter::MouseDown() {
	//UE_LOG(LogTemp, Warning, TEXT("in mouseDown"));
	if (useMouse) {
		if (MyPC != nullptr) {
			FHitResult Hit;
			MyPC->GetHitResultUnderCursor(ECC_Pawn, false, Hit);
			if (Hit.bBlockingHit) {
				if (Hit.Actor != NULL) {
					clickedActor = Hit.GetActor();
					//UE_LOG(LogTemp, Warning, TEXT("Clicked actors name: %s"), *clickedActor->GetName());
					if (clickedActor->GetClass()->IsChildOf(ADraggableBlock::StaticClass())) {
					//	UE_LOG(LogTemp, Warning, TEXT("object is draggable"));
						clickedBlock = Cast<ADraggableBlock>(clickedActor);
						clickedBlock->OnClicked();
					}
				}
			}
		}
		
	}
}

void APlayerCharacter::MouseUp() {
	if (useMouse) {
	//	UE_LOG(LogTemp, Warning, TEXT("in mouseUp"));
		if (clickedBlock != nullptr) {
			clickedBlock->OnReleased();
			clickedBlock = nullptr;
		}
	}
}

