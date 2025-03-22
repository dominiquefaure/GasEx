// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GxActionContext.h"
#include "GxActionGraphInstance.generated.h"

class UGxAbilitySystemComponent;
class UGxActionGraph;
class UGxActionNode_Base;


/**
 *
 */
UCLASS()
class GXACTIONS_API UGxActionGraphInstance : public UObject
{
	GENERATED_BODY()

public:

	UGxActionGraphInstance();


	void SetGraph(UGxActionGraph* Graph);


	void OnInputTriggered( FGameplayTag InputTag );

	// function for activation of the Cancel window
	void OnCancelWindowStart( FString WindowName );
	void OnCancelWindowEnd( FString WindowName );


	void TryStartAction( FGxActionContext& ExecutionContext );

private:

	void ProcessInProgressState();
	void ProcessFinishedState();



private:

	TQueue<FGameplayTag>					InputQueue;


	// the Graph instanciated
	TObjectPtr<UGxActionGraph>				Graph;
	TObjectPtr<UGxActionNode_Base>			CurrentGraphNode;

	bool									IsCancelWindowsActive;
	TArray<FString>							CancelWindows;

};