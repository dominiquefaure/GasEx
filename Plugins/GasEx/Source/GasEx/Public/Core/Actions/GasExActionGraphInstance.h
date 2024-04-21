// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "GasExActionGraphInstance.generated.h"

class UGasExAbilitySystemComponent;

class UGasExActionGraph;
class UGasExActionNode;


UENUM()
enum class EGasExActionGraphState : uint8
{
	NoAction		=	0 ,	// No action currently playing, graph is in waiting state
	ActionInProgres	=	1,	// an Action is currently in Progress
	ActionFinished	=	9, // the Current Action just finished will go back to NoAction if no follow up action can be launched
};

/**
 *
 */
UCLASS()
class GASEX_API UGasExActionGraphInstance : public UObject
{
	GENERATED_BODY()

public:

	void SetAbilitySystem(UGasExAbilitySystemComponent* AbilitySystem);
	void SetGraph(UGasExActionGraph* Graph);

	// do necessary actions when an input is Triggered
	void OnInputTriggered( FGameplayTag InputTag );

	virtual void Tick();


	// function for activation of the Cancel window
	void OnCancelWindowStart( FString WindowName );
	void OnCancelWindowEnd( FString WindowName );

// Methods
private:

	// process the different States of the Graph instance, called from Tick function
	void ProcessWaitingState();
	void ProcessActionInProgressState();
	void ProcessActionFinishedState();

	bool ExecuteAction( UGasExActionNode*  NewActionNode );

	void OnAbilityEnded( const FAbilityEndedData& EndedData );

	bool CanExecuteLinkedAction( FGameplayTag InputTag , UGasExActionNodeLink* Link );

	bool canExecuteAction( UGasExActionNode* Node ,FGameplayTag InputTag );

	bool IsCancelWindowActive( FString WindowName );

private:
	// State of the Instance
	EGasExActionGraphState					CurrentState;

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystemComponent;

	// the Graph instanciated
	TObjectPtr<UGasExActionGraph>			Graph;
	TObjectPtr<UGasExActionNode>			CurrentGraphNode;


	TQueue<FGameplayTag>					InputQueue;

	bool									IsCancelWindowsActive;
	TArray<FString>							CancelWindows;

};
