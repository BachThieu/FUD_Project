// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetOverhead.h"
#include "Components/TextBlock.h"

void UWidgetOverhead::SetDisplayText(FString TextoDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextoDisplay));

	}
}

void UWidgetOverhead::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_None:
		Role = FString("None");
		break;
	}
	FString LocalRoleString = FString::Printf(TEXT("Local Role: %s"), *Role);
	SetDisplayText(LocalRoleString);

}

void UWidgetOverhead::NativeDestruct() 
{
	RemoveFromParent();
	Super::NativeDestruct();

}
