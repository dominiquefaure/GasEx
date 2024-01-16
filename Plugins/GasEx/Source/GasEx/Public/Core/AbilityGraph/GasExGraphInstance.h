// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasExGraphInstance.generated.h"


class UGasExGraph;
class UGasExGraphLink;
class UGasExGraphNodeBase;
class UGasExGraphNodeEntry;
class UGasExGraphNodeAbility;

class UGasExAbilitySystemComponent;


/**
 *
 */
UCLASS( )
class GASEX_API UGasExGraphInstance : public UObject
{
	GENERATED_BODY()

public:

	void SetAbilitySystem( UGasExAbilitySystemComponent* AbilitySystem );
	void SetGraph( UGasExGraph* Graph );

	// try to launch the next node, breaking the current one if needed
	bool TryExecuteNextNode();


private:

	// Get the next Ability that can be activated
	UGasExGraphNodeAbility* GetNextActivableAbility( UGasExGraphNodeBase*Node );

	bool ExecuteAbilityNode( UGasExGraphNodeAbility* Node );

private:

	UGasExAbilitySystemComponent* AbilitySystem;

	// the Graph instanciated
	TObjectPtr<UGasExGraph>	Graph;
	TObjectPtr<UGasExGraphNodeAbility> CurrentAbilityNode;

};
