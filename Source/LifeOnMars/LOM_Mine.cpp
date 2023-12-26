// Fill out your copyright notice in the Description page of Project Settings.

#include "LOM_Mine.h"

// Sets default values
ALOM_Mine::ALOM_Mine()
{
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ALOM_Mine::BeginPlay()
{
	Super::BeginPlay();
	
}

