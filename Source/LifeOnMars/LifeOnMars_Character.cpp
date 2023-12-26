// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeOnMars_Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "LifeOnMars.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

// Sets default values
ALifeOnMars_Character::ALifeOnMars_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SocketOffset = FVector(0.f, 60.f, 90.f);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->FieldOfView = 110;
	E_Activity = ECharacterActivity::EWalk;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;


}

// Called when the game starts or when spawned
void ALifeOnMars_Character::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ALifeOnMars_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ALifeOnMars_Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ALifeOnMars_Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALifeOnMars_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALifeOnMars_Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALifeOnMars_Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALifeOnMars_Character::TouchStopped);

	// VR headset functionality
	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ALifeOnMars_Character::OnResetVR);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ALifeOnMars_Character::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ALifeOnMars_Character::StopRun);

}

//void ALifeOnMars_Character::OnResetVR()
//{
//	// If Deverse is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Deverse.Build.cs is not automatically propagated
//	// and a linker error will result.
//	// You will need to either:
//	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
//	// or:
//	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
//	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
//}

void ALifeOnMars_Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ALifeOnMars_Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ALifeOnMars_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALifeOnMars_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALifeOnMars_Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		if (E_Activity == ECharacterActivity::ERun && Value <= 0.0f) {
			UpdateActivity(ECharacterActivity::EWalk);
		}
	}
}

void ALifeOnMars_Character::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);

		if (E_Activity == ECharacterActivity::ERun) {
			UpdateActivity(ECharacterActivity::EWalk);
		}
	}
}

void ALifeOnMars_Character::Run()
{
	if (E_Activity == ECharacterActivity::EWalk) {
		UpdateActivity(ECharacterActivity::ERun);
		
		
	}
}

void ALifeOnMars_Character::StopRun()
{
	if (E_Activity == ECharacterActivity::ERun)
		UpdateActivity(ECharacterActivity::EWalk);
}

void ALifeOnMars_Character::HCrouch()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (CanCrouch() && E_Activity != ECharacterActivity::ECrouch)
	{
		UpdateActivity(ECharacterActivity::ECrouch);
		Crouch();
	}
	else
	{
		if (E_Activity == ECharacterActivity::ECrouch) {
			UnCrouch();
			UpdateActivity(ECharacterActivity::EWalk);
		}
	}
}

void ALifeOnMars_Character::OnRep_Activity()
{
	switch (E_Activity)
	{
	case ECharacterActivity::EIdle:
		break;
	case ECharacterActivity::EWalk:
		break;
	case ECharacterActivity::ERun:
		break;
	default:
		break;
	}
}


bool ALifeOnMars_Character::Trace_Hit(int Far, float Radius, FHitResult &Hits)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3));
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> A;
	A.Add(GetOwner());
	bool bHasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), FollowCamera->K2_GetComponentLocation(), FollowCamera->K2_GetComponentLocation() + (FollowCamera->GetForwardVector() * Far), Radius, ObjectTypesArray, true, A, EDrawDebugTrace::None, Hits, true);
	return bHasHit;
}

void ALifeOnMars_Character::OnRep_IncreaseSpeed()
{
	
}

void ALifeOnMars_Character::R_IncreaseSpeed(float value)
{
	IncreaseSpeed = value;
	OnRep_IncreaseSpeed();
}

void ALifeOnMars_Character::SetSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ALifeOnMars_Character::UpdateActivity(ECharacterActivity InActivity)
{
	if (GetLocalRole() < ROLE_Authority)
		ServerUpdateActivity(InActivity);

	E_Activity = InActivity;

	switch (E_Activity) {
	case ECharacterActivity::EIdle:
		break;
	case ECharacterActivity::EWalk:
		SetSpeed(DefaultSpeed + IncreaseSpeed);
		break;
	case ECharacterActivity::ERun:
		SetSpeed(RunSpeed + IncreaseSpeed);
		break;
	case ECharacterActivity::ECrouch:
		SetSpeed(DefaultSpeed + IncreaseSpeed);
		break;
	}

	OnRep_Activity();
}

void ALifeOnMars_Character::ServerUpdateActivity_Implementation(ECharacterActivity InActivity)
{
	UpdateActivity(InActivity);
}

bool ALifeOnMars_Character::ServerUpdateActivity_Validate(ECharacterActivity InActivity)
{
	return true;
}

void ALifeOnMars_Character::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALifeOnMars_Character, E_Activity);
	DOREPLIFETIME(ALifeOnMars_Character, IncreaseSpeed);

}