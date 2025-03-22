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


	void SetAbilitySystem(UGxAbilitySystemComponent* AbilitySystem);
	void SetGraph(UGxActionGraph* Graph);


	void OnInputTriggered( FGameplayTag InputTag );


	virtual void Tick( FGxActionContext& ExecutionContext );

	// function for activation of the Cancel window
	void OnCancelWindowStart( FString WindowName );
	void OnCancelWindowEnd( FString WindowName );

private:

	// process the different States of the Graph , called from Tick function
	void ProcessWaitingState( FGxActionContext& ExecutionContext );
	void ProcessInProgressState();
	void ProcessFinishedState();

	void OnAbilityEnded( const FAbilityEndedData& EndedData );


	bool TryExecuteAction( UGxActionNode_Base* InActionNode );

private:

	TObjectPtr<UGxAbilitySystemComponent>	AbilitySystemComponent;

	TQueue<FGameplayTag>					InputQueue;


	// the Graph instanciated
	TObjectPtr<UGxActionGraph>				Graph;
	TObjectPtr<UGxActionNode_Base>			CurrentGraphNode;

	bool									IsCancelWindowsActive;
	TArray<FString>							CancelWindows;

};