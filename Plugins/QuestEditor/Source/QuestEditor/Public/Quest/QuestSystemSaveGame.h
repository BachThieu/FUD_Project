//Copyright 2020 Marchetti S. Alfredo I. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Quest/QuestTypes.h"
#include "QuestSystemSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class QUESTEDITOR_API UQuestSystemSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	//For replication
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	//------------------------------------Manager Variables------------------------
	//--------------------------------------Quest 
	UPROPERTY(Replicated)
		TArray<FQuestRep> QuestInventorySaved;

	UPROPERTY(Replicated)
		TArray<FCompletedQuestTrack> CompletedQuestsTrackSaved;
	
	UPROPERTY(Replicated)
		TArray<FQuestTrack> QuestsTrackSaved;

	UPROPERTY(Replicated)
		TArray<FQuestFailTrack> QuestsFailTrackSaved;

	//------------------------------------------Dialogs

	UPROPERTY()
		TArray<FQuestRep> DialogsInventorySaved;

	UPROPERTY()
		TArray<FCompletedQuestTrack> CompletedDialogsTrackSaved;

	UPROPERTY()
		TArray<FQuestTrack> DialogsTrackSaved;

	UPROPERTY()
		TArray<FQuestFailTrack> DialogsFailTrackSaved;

};
