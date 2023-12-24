//Copyright 2020 Marchetti S. Alfredo I. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"

#include "QuestEditorSubsystem.generated.h"

//--------------------------------------------------------------------
//----------------------------------DISPATCHERS DECLARATIONS
//--------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTESTSUBSYSTEM);


/**
 *	This is the editor subsystem for the Quest Editor
 *	For now, i cannot use inside editor widgets, so is not that useful.
 *	For testing purposes.
 */
UCLASS()
class QUESTEDITORDEV_API UQuestEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	
	// Begin USubsystem
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	// End USubsystem
	//virtual void Deinitialize() override;
	
	//--------------------------------------------------------------------
	//----------------------------------DISPATCHERS
	//--------------------------------------------------------------------
		/*Called when a quest is accepted*/
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Quest")
		FTESTSUBSYSTEM TESTSUBSYSTEM;



	//--------------------------------------------------------------------
	//----------------------------------VARIABLES
	//--------------------------------------------------------------------

	/*Warever*/
	UPROPERTY(BlueprintReadWrite, Category = "Quest")
		FString QuestString = "Questerina";

};
