// Fill out your copyright notice in the Description page of Project Settings.

#include "LOM_Weapon.h"

// Sets default values
ALOM_Weapon::ALOM_Weapon()
{
	bReplicates = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(RootComponent);

	// CapsuleComponent initialization
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(44.f, 22.f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CapsuleComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

}

// Called when the game starts or when spawned
void ALOM_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}


