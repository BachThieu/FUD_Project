// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "zPlayerStatez.generated.h"

/**
 * 
 */
UCLASS()
class LIFEONMARS_API AzPlayerStatez : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Player Name
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerName_Implementation(const FString& InNewName);

	UFUNCTION(BlueprintCallable)
	virtual void SetPlayerName(const FString& S);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetPlayerName(const FString& S);

	virtual void OnRep_PlayerName() override;


	// Set Skin
	UFUNCTION(BlueprintCallable)
	void UpdateSkin_Implementation(const int& Id);

	UFUNCTION(BlueprintCallable)
	void SetCurrentSkin(const int& Id);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSetSkin(const int& Id);
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		int SkinId;
};
