// Fill out your copyright notice in the Description page of Project Settings.


#include "LOM_FunctionLibrary.h"

FString ULOM_FunctionLibrary::ReadStringFromFile(FString FilePath, bool& bOut, FString& OutString)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath)) {
		bOut = false;
		OutString = FString::Printf(TEXT("Read String failed - file doesn't exist '%s'"), *FilePath);
		return "";
	}

	FString ReString = "";

	if (!FFileHelper::LoadFileToString(ReString, *FilePath)) {
		bOut = false;
		OutString = FString::Printf(TEXT("Read String failed - file doesn't exist '%s'"), *FilePath);
		return "";
	}

	bOut = true;
	OutString = FString::Printf(TEXT("Read String From File Succeeded '%s'"), *FilePath);
	return ReString;
}

void ULOM_FunctionLibrary::Calculator_XP(int level, int xp, int& XP_Out, int& XP_Need)
{
	int y = level + 81;

	if (level == 1) 
	{
		int x = ((y)-82) * 0.02;
		XP_Out = ((x + 0.1) * (level + 81) * y + 1);
		XP_Need = XP_Out - xp;
	}
	else {
		int x = ((y)-82) * 0.02;
		int z = (x + 0.1) * (level + 81);
		XP_Out = (z * y + 1) + (z * (y-1) + 1);
		XP_Need = XP_Out - xp;
	}

}



