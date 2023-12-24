//Copyright 2020 Marchetti S. Alfredo I. All Rights Reserved.


#include "Quest/QuestSystemSaveGame.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

void UQuestSystemSaveGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicated (no notify)
	DOREPLIFETIME(UQuestSystemSaveGame, QuestInventorySaved);
	DOREPLIFETIME(UQuestSystemSaveGame, CompletedQuestsTrackSaved);
	DOREPLIFETIME(UQuestSystemSaveGame, QuestsTrackSaved);
	DOREPLIFETIME(UQuestSystemSaveGame, QuestsFailTrackSaved);
}
