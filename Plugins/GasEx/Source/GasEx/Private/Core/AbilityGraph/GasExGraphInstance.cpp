// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "Core/AbilityGraph/GasExGraphInstance.h"

#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"
#include "Core/AbilityGraph/GasExGraph.h"
#include "Core/AbilityGraph/GasExGraphLink.h"
#include "Core/AbilityGraph/GasExGraphNodeAbility.h"

//---------------------------------------------------------------------------------------------
void UGasExGraphInstance::SetAbilitySystem( UGasExAbilitySystemComponent* InAbilitySystem )
{
	AbilitySystem	=	InAbilitySystem;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExGraphInstance::SetGraph( UGasExGraph* InGraph )
{
	Graph				=	InGraph;
	CurrentAbilityNode	=	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExGraphInstance::TryExecuteNextNode()
{
	if( Graph == nullptr )
	{
		return false;
	}
	UGasExGraphNodeAbility* NextAbilityNode	=	nullptr;

	// if no Ability executed yet
	if( CurrentAbilityNode == nullptr )
	{
		NextAbilityNode	=	GetNextActivableAbility( Graph->EntryNode );
	}
	else
	{
		NextAbilityNode	=	GetNextActivableAbility( CurrentAbilityNode );
	}

	if( ExecuteAbilityNode( NextAbilityNode ) )
	{
		return true;
	}

	// reset the node graph if no ability found
	CurrentAbilityNode	=	nullptr;

	return false;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
UGasExGraphNodeAbility* UGasExGraphInstance::GetNextActivableAbility( UGasExGraphNodeBase* Node )
{

	for( UGasExGraphLink* Link : Node->Links )
	{
		// to do add condition of executions
		UGasExGraphNodeAbility* AbilityNode	=	Cast<UGasExGraphNodeAbility>( Link->EndNode );
		if( AbilityNode )
		{
			return AbilityNode;
		}
	}


	return nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExGraphInstance::ExecuteAbilityNode( UGasExGraphNodeAbility* Node )
{
	check( AbilitySystem );

	if( Node == nullptr )
	{
		return false;
	}

	// if the Activation succeed, made the node the new active one
	if( AbilitySystem->TryActivateExAbility( Node->AbilityTag ) )
	{
		CurrentAbilityNode	=	Node;
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------
