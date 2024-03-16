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

// Methods
private:

	bool ExecuteAction( UGasExActionNode*  NewActionNode );

	void OnAbilityEnded( const FAbilityEndedData& EndedData );

	// try to execute one of the follow up actions of the current one
	bool TryExecuteFollowUpAction();

private:

	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystemComponent;

	// the Graph instanciated
	TObjectPtr<UGasExActionGraph>	Graph;
	TObjectPtr<UGasExActionNode> CurrentGraphNode;

};
