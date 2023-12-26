// Fill out your copyright notice in the Description page of Project Settings.


#include "MetahumanAnimInstance.h"
#include "MetahumanCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"    
#include "LifeOnMars/Weapon/Weapon.h"
void UMetahumanAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MetahumanCharacter = Cast<AMetahumanCharacter>(TryGetPawnOwner()); 

}

void UMetahumanAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (MetahumanCharacter == nullptr)
	{
		MetahumanCharacter = Cast<AMetahumanCharacter>(TryGetPawnOwner());
	}
	if (MetahumanCharacter == nullptr) return;

	FVector Velocity = MetahumanCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
	
	bIsInAir = MetahumanCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = MetahumanCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = MetahumanCharacter->IsWeaponEquipped();
	EquippedWeapon = MetahumanCharacter->GetEquippedWeapon();
	bIsCrouched = MetahumanCharacter->bIsCrouched;
	bAiming = MetahumanCharacter->IsAiming();
	TurningInPlace = MetahumanCharacter->GetTurningInPlace();
	bRotateRootBone = MetahumanCharacter->ShouldRotateRootBone();

      
	// Offset Yaw for Strafing
	FRotator AimRotation = MetahumanCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MetahumanCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation); 
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;


	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = MetahumanCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = MetahumanCharacter->GetAO_Yaw();
	AO_Pitch = MetahumanCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && MetahumanCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		MetahumanCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));  

		if (MetahumanCharacter->IsLocallyControlled())
		{
			bLocallyControlled = true;
			FTransform RightHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("hand_r"), ERelativeTransformSpace::RTS_World);
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() 
				+ (RightHandTransform.GetLocation() - MetahumanCharacter->GetHitTarget()));
			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 20.f);
		}
		else
		{
			bLocallyControlled = true;
			FTransform RightHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("hand_r"), ERelativeTransformSpace::RTS_World);
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation()
				+ (RightHandTransform.GetLocation() - MetahumanCharacter->GetHitTarget()));
			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 20.f); 
		}
		

		FTransform MuzzleTipTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("MuzzleFlash"), ERelativeTransformSpace::RTS_World);
		FVector MuzzleX(FRotationMatrix(MuzzleTipTransform.GetRotation().Rotator()).GetUnitAxis(EAxis::X));
		//DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation() , MuzzleTipTransform.GetLocation() + MuzzleX * 10000.f, FColor::Red);
		//DrawDebugLine(GetWorld(), MuzzleTipTransform.GetLocation(), MetahumanCharacter->GetHitTarget(), FColor::Orange); 
	}


	 

}
