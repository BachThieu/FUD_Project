// Fill out your copyright notice in the Description page of Project Settings.


#include "zPlayerStatez.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

void AzPlayerStatez::BeginPlay()
{
	Super::BeginPlay();
}


void AzPlayerStatez::UpdatePlayerName_Implementation(const FString& InNewName)
{
	SetPlayerName(InNewName);
}

void AzPlayerStatez::SetPlayerName(const FString& S)
{
	if (GetLocalRole() < ROLE_Authority) {
		ServerSetPlayerName(S);
	}
	Super::SetPlayerName(S);
	OnRep_PlayerName();
}

void AzPlayerStatez::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();
}

void AzPlayerStatez::ServerSetPlayerName_Implementation(const FString& S)
{
	SetPlayerName(S);
}

bool AzPlayerStatez::ServerSetPlayerName_Validate(const FString& S)
{
	return true;
}

// Skin Id
void AzPlayerStatez::UpdateSkin_Implementation(const int& Id)
{
	SetCurrentSkin(Id);
}

void AzPlayerStatez::SetCurrentSkin(const int& Id)
{
	if (GetLocalRole() < ROLE_Authority)
		ServerSetSkin(Id);

	SkinId = Id;
}

void AzPlayerStatez::ServerSetSkin_Implementation(const int& Id)
{
	SetCurrentSkin(Id);
}

bool AzPlayerStatez::ServerSetSkin_Validate(const int& Id)
{
	return true;
}

void AzPlayerStatez::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AzPlayerStatez, SkinId);
}