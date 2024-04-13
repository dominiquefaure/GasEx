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

// Methods
private:

	bool ExecuteAction( UGasExActionNode*  NewActionNode );

	void OnAbilityEnded( const FAbilityEndedData& EndedData );

	// try to execute one of the follow up actions of the current one
	bool TryExecuteFollowUpAction();

	// try cancel the current action according to the given input
	bool TryCancelAction( FGameplayTag InputTag );

	bool TryExecuteLinkedAction( FGameplayTag InputTag , UGasExActionNodeLink* Link );

	bool canExecuteAction( UGasExActionNode* Node ,FGameplayTag InputTag );


	void ProcessInputs( );


private:
	// State of the Instance
	EGasExActionGraphState					CurrentState;

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystemComponent;

	// the Graph instanciated
	TObjectPtr<UGasExActionGraph>			Graph;
	TObjectPtr<UGasExActionNode>			CurrentGraphNode;


	TQueue<FGameplayTag>					InputQueue;
};
