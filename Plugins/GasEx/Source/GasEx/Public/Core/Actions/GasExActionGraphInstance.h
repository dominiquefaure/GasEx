// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "GasExActionGraphInstance.generated.h"

class UGasExAbilitySystemComponent;

class UGasExActionGraph;
class UGasExActionNode;

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

	bool LaunchFirstAction();

	// do necessary actions when an input is Triggered
	void ProcessInputTriggered( FGameplayTag InputTag );

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

private:

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystemComponent;

	// the Graph instanciated
	TObjectPtr<UGasExActionGraph>	Graph;
	TObjectPtr<UGasExActionNode> CurrentGraphNode;

	// Critical Section between process input and Ability Ended
	mutable FCriticalSection ProcessCritialSection;
};
