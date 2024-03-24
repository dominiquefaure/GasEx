// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/Actions/GasExActionGraphInstance.h"
#include "Core/Actions/GasExActionGraph.h"
#include "Core/Actions/GasExActionNode.h"
#include "Core/Actions/GasExActionNodeLink.h"
#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::SetAbilitySystem(UGasExAbilitySystemComponent* InAbilitySystem)
{
	AbilitySystemComponent = InAbilitySystem;
	AbilitySystemComponent->OnAbilityEnded.AddUObject( this , &UGasExActionGraphInstance::OnAbilityEnded );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::SetGraph(UGasExActionGraph* InGraph)
{
	Graph = InGraph;
	CurrentGraphNode = nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::LaunchFirstAction()
{
	if( CurrentGraphNode == nullptr )
	{
		TArray<UGasExActionNode*>	StartActions	=	Graph->GetAllStartActions();

		if( StartActions.Num() > 0 )
		{
			ExecuteAction( StartActions[0] );

			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::ExecuteAction( UGasExActionNode*  NewActionNode )
{
	check( AbilitySystemComponent );

	if( NewActionNode == nullptr )
	{
		return false;
	}

	// if the Activation succeed, made the node the new active one
	if( AbilitySystemComponent->TryActivateExAbility( NewActionNode->AbilityTag ) )
	{
		// Cancel the current Node
		if( CurrentGraphNode != nullptr )
		{
			AbilitySystemComponent->CancelExAbility( CurrentGraphNode->AbilityTag );
		}

		CurrentGraphNode	=	NewActionNode;
		return true;
	}

	return false;

}
//---------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExActionGraphInstance::OnAbilityEnded( const FAbilityEndedData& EndedData )
{
	if( CurrentGraphNode != nullptr )
	{
		// if the Ability ended is the one associated to the current Action node
		if( CurrentGraphNode->AbilityTag == AbilitySystemComponent->GetExAbilityTagFromHandle( EndedData.AbilitySpecHandle ) )
		{
			if( !TryExecuteFollowUpAction() )
			{
				CurrentGraphNode	=	nullptr;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::TryExecuteFollowUpAction()
{
	check( CurrentGraphNode )

	for( UGasExActionNodeLink* Link : CurrentGraphNode->Links )
	{
		if( Link->TargetNode )
		{
			ExecuteAction( Link->TargetNode );
			return true;
		}
	}

	return false;
}
//-----------------------------------------------------------------------------------------
