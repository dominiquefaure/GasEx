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

	CurrentState	=	EGasExActionGraphState::NoAction;
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
void UGasExActionGraphInstance::Tick()
{
	ProcessInputs();

	if( CurrentState == EGasExActionGraphState::ActionFinished )
	{
		if( !TryExecuteFollowUpAction() )
		{
			CurrentGraphNode	=	nullptr;
			CurrentState		=	EGasExActionGraphState::NoAction;
		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "next action have beeen found" ) );
		}
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::OnInputTriggered( FGameplayTag InputTag )
{
	InputQueue.Enqueue( InputTag );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::ProcessInputs()
{
	UE_LOG( LogTemp , Warning , TEXT( "Start ProcessInputs" ) );

	FGameplayTag InputTag;

	if( InputQueue.Dequeue( InputTag ) )
	{
		if( CurrentGraphNode == nullptr )
		{
			TArray<UGasExActionNode*>	StartActions	=	Graph->GetAllStartActions();

			for( UGasExActionNode* StartNode : StartActions )
			{
				if( canExecuteAction( StartNode , InputTag ) )
				{
					ExecuteAction( StartNode );
				}
			}
		}
		else
		{
			TryCancelAction( InputTag );
		}
		UE_LOG( LogTemp , Warning , TEXT( "End ProcessInputs" ) );
	}
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

	if( CurrentGraphNode != nullptr )
	{
		if( NewActionNode->AbilityTag == CurrentGraphNode->AbilityTag )
		{
			UE_LOG( LogTemp , Warning , TEXT( "Error try to cancel an acton by itself!!!!!!!!" ) );

			return false;
		}
	}


	// if the Activation succeed, made the node the new active one
	if( AbilitySystemComponent->TryActivateExAbility( NewActionNode->AbilityTag ) )
	{
		// Cancel the current Node
		if( CurrentGraphNode != nullptr )
		{
			FGameplayTag PreviousAbilityTag	=	CurrentGraphNode->AbilityTag;
			CurrentGraphNode	=	nullptr;
			AbilitySystemComponent->CancelExAbility( PreviousAbilityTag );
		}

		CurrentGraphNode	=	NewActionNode;
		CurrentState		=	EGasExActionGraphState::ActionInProgres;

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
			CurrentState	=	EGasExActionGraphState::ActionFinished;

		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "Ability ened but not same Node !!!!!!" ) );
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

//-----------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::TryCancelAction( FGameplayTag InputTag )
{
	if( CurrentGraphNode != nullptr )
	{
		for( UGasExActionNodeLink* Link : CurrentGraphNode->Links )
		{
			if( TryExecuteLinkedAction( InputTag , Link ) )
			{
				return true;
			}
		}
	}
	return false;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::TryExecuteLinkedAction( FGameplayTag InputTag , UGasExActionNodeLink* Link )
{

	if( Link->TargetNode != nullptr )
	{
		if( canExecuteAction( Link->TargetNode , InputTag ) )
		{
			ExecuteAction( Link->TargetNode );
			return true;
		}
	}

	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::canExecuteAction( UGasExActionNode* Node , FGameplayTag InputTag )
{
	if( Node->InputTag.MatchesTagExact( InputTag ) )
	{
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------
