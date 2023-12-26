// Fill out your copyright notice in the Description page of Project Settings.

#include "LOM_Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"



// Sets default values
ALOM_Projectile::ALOM_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetSimulatePhysics(false);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->IgnoreActorWhenMoving(GetOwner(), true);
	SetRootComponent(CollisionBox);


	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	Projectile->bRotationFollowsVelocity = true;
	Projectile->InitialSpeed = InitialSpeed;
	Projectile->MaxSpeed = InitialSpeed;
}

// Called when the game starts or when spawned
void ALOM_Projectile::BeginPlay()
{
	Super::BeginPlay();
	Projectile->InitialSpeed = InitialSpeed;
	Projectile->MaxSpeed = InitialSpeed;
}

void ALOM_Projectile::StartDestroyTimer()
{

}

void ALOM_Projectile::DestroyTimerFinished()
{
	Destroy();
}

void ALOM_Projectile::Destroyed()
{
	if (ImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorTransform());
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
	Super::Destroyed();
}

void ALOM_Projectile::SpawnTrailSystem()
{
}

void ALOM_Projectile::ExplodeDamage()
{
}
