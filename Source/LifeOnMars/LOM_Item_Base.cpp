// Fill out your copyright notice in the Description page of Project Settings.


#include "LOM_Item_Base.h"

// Sets default values
ALOM_Item_Base::ALOM_Item_Base()
{
	bReplicates = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ALOM_Item_Base::BeginPlay()
{
	Super::BeginPlay();
	
}
