// Fill out your copyright notice in the Description page of Project Settings.


#include "LOM_AC_WIdget_NameSpace.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values for this component's properties
ULOM_AC_WIdget_NameSpace::ULOM_AC_WIdget_NameSpace()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5;
}

// Called when the game starts
void ULOM_AC_WIdget_NameSpace::BeginPlay()
{
	Super::BeginPlay();

}

void ULOM_AC_WIdget_NameSpace::Check()
{
	Set_Hide();

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> A;
	A.Add(GetOwner());
	TArray<FHitResult> Hits;
	bool bHasHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		GetOwner()->GetActorLocation(),
		GetOwner()->GetActorLocation(),
		Radius,
		traceObjectTypes,
		false,
		A,
		EDrawDebugTrace::None,
		Hits,
		true);

	for (auto & h : Hits) 
	{
		AActor* Actor;
		Actor = h.GetActor();

		if (h.GetActor()) 
		{
			UWidgetComponent* wg = Actor->FindComponentByClass<UWidgetComponent>();
			if (wg && wg->GetWidgetSpace() == EWidgetSpace::Screen && wg->IsVisible() == false) {
				Actors.AddUnique(Actor);
				wg->SetVisibility(true);
			}
		}

	}
}

void ULOM_AC_WIdget_NameSpace::Set_Hide()
{
	for (auto& a : Actors) {
		if ((a->GetActorLocation() - GetOwner()->GetActorLocation()).Length() > Radius) 
		{
			UWidgetComponent* wg = a->FindComponentByClass<UWidgetComponent>();
			if (wg && wg->GetWidgetSpace() == EWidgetSpace::Screen && wg->IsVisible() == true)
			{
				wg->SetVisibility(false);
				/*if(a)
				Actors.Remove(a);*/
			}
		}
	}
}

// Called every frame
void ULOM_AC_WIdget_NameSpace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Check();

}

