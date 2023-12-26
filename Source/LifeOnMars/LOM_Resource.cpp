// Fill out your copyright notice in the Description page of Project Settings.


#include "LOM_Resource.h"

// Sets default values
ALOM_Resource::ALOM_Resource()
{
	bReplicates = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetupAttachment(RootScene);
}

// Called when the game starts or when spawned
void ALOM_Resource::BeginPlay()
{
	Super::BeginPlay();
	
}

