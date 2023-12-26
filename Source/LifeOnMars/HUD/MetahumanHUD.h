// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MetahumanHUD.generated.h"

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()
public:
	class UTexture2D* CrosshairCenter;
	UTexture2D* CrosshairLeft;
	UTexture2D* CrosshairRight;
	UTexture2D* CrosshairTop;
	UTexture2D* CrosshairBottom;
	float CrosshairSpread;
	FLinearColor CrosshairColor;


};
/**
 * 
 */
UCLASS()
class LIFEONMARS_API AMetahumanHUD : public AHUD
{
	GENERATED_BODY()
public:     
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> CharacterOverlayClass;

	class UCharacterOverlay* CharacterOverlay;

protected:
	virtual void BeginPlay() override;
	void AddCharacterOverlay();
private:
	FHUDPackage HUDPackage;
	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread,FLinearColor CrosshairColor);

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;

public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package)
	{
		HUDPackage = Package;
	}
	
};
