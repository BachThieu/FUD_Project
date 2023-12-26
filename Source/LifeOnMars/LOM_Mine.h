// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LOM_Mine.generated.h"

UCLASS()
class LIFEONMARS_API ALOM_Mine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALOM_Mine();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
		UStaticMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
