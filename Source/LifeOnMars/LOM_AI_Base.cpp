// Fill out your copyright notice in the Description page of Project Settings.


#include "LOM_AI_Base.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ALOM_AI_Base::ALOM_AI_Base()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALOM_AI_Base::BeginPlay()
{
	Super::BeginPlay();
	Create();
	
}

void ALOM_AI_Base::Create()
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	UAnimInstance* AnimInstance = SkeletalMesh->GetAnimInstance();

	if (AnimInstance)
	{
		PlayAnimMontage(AnimMontage, 1.f);
		float DelayTime = AnimInstance->UAnimInstance::Montage_Play(AnimMontage,
			1.000000,
			EMontagePlayReturnType::MontageLength,
			0.000000,
			true);
	}
}

void ALOM_AI_Base::Despawn()
{
	if (GetController())
	{
		GetController()->SetLifeSpan(5.f);
		GetController()->UnPossess();
		FVector Loc = GetActorLocation() + GetActorForwardVector();
		UKismetSystemLibrary::MoveComponentTo(GetRootComponent(),
			FVector(Loc),
			FRotator(0.000000, 0.000000, 0.000000),
			false, false, 1.000000, false,
			EMoveComponentAction::Move,
			FLatentActionInfo(8, 1882238094, TEXT(""),
				this));
		SetLifeSpan(1);
	}
	else {
		Destroy(true, true);
	}
}

void ALOM_AI_Base::SetBehavior()
{
	AAIController* AIPC = Cast<AAIController>(GetController());
	if (AIPC)
	{
		if (BehaviorTree) {
			AIPC->RunBehaviorTree(BehaviorTree);
		}
	}
}


// Called to bind functionality to input
void ALOM_AI_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALOM_AI_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SetBehavior();
}

void ALOM_AI_Base::PlayMontage(class UAnimMontage* MontageToPlay)
{
	if (GetLocalRole() < ROLE_Authority) {
		ServerPlayMontage(MontageToPlay);
	}

	NetPlayMontage(MontageToPlay);
}

void ALOM_AI_Base::ServerPlayMontage_Implementation(class UAnimMontage* MontageToPlay)
{
	PlayMontage(MontageToPlay);
}

bool ALOM_AI_Base::ServerPlayMontage_Validate(class UAnimMontage* MontageToPlay)
{
	return true;
}

void ALOM_AI_Base::NetPlayMontage_Implementation(class UAnimMontage* MontageToPlay)
{
	if (GetMesh()->GetAnimInstance())
		GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
}