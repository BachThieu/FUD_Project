// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LOM_FunctionLibrary.generated.h"
class APlayerController;
/**
 * 
 */
UCLASS()
class LIFEONMARS_API ULOM_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable, Category = "Set Mouse Mid Montion")
		//static FORCEINLINE void Set_Mouse_Mid_Montion(APlayerController* AplayerController);

	UFUNCTION(BlueprintCallable, Category = "Read Write File")
		static FString ReadStringFromFile(FString FilePath, bool& bOut, FString& OutString);

	//UFUNCTION(BlueprintCallable, Category = "Read Write File")
	//	static void WriteStringFromFile(FString FilePath, FString String, bool& bOut, FString& OutString);
	
	UFUNCTION(BlueprintCallable, Category = "Calculator")
		static void Calculator_XP(int level, int xp , int& XP_Out, int& XP_Need);
	
};

