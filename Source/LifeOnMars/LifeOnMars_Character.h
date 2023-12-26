// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LifeOnMars.h"
#include "LifeOnMars_Character.generated.h"



UCLASS()
class LIFEONMARS_API ALifeOnMars_Character : public ACharacter
{

	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	ALifeOnMars_Character();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;



protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void Run();

	void StopRun();

	void HCrouch();

	void SetSpeed(float speed);

	void UpdateActivity(ECharacterActivity InActivity);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUpdateActivity(ECharacterActivity InActivity);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UPROPERTY(ReplicatedUsing = OnRep_Activity, EditAnywhere, BlueprintReadWrite)
		ECharacterActivity E_Activity;

	// Modify speed
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
		float DefaultSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
		float RunSpeed = 600.f;

	UFUNCTION(BlueprintCallable, meta = (Category, OverrideNativeName = "OnRep_Activity"))
		virtual void OnRep_Activity();

	UFUNCTION(BlueprintCallable)
		bool Trace_Hit(int Far, float Radius, FHitResult &Hit);


	// IncreaseSpeed
	UPROPERTY(ReplicatedUsing = OnRep_IncreaseSpeed, EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float IncreaseSpeed = 0.f;

	UFUNCTION(BlueprintCallable, meta = (Category, OverrideNativeName = "OnRep_IncreaseSpeed"))
		virtual void OnRep_IncreaseSpeed();

	UFUNCTION(BlueprintCallable)
		void R_IncreaseSpeed(float value);

};
