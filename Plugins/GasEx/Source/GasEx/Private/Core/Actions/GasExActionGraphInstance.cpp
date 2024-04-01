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
void UGasExActionGraphInstance::ProcessInputTriggered( FGameplayTag InputTag )
{
	UE_LOG( LogTemp , Warning , TEXT( "Start ProcessInputTriggered" ) );

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
		FScopeLock ScopeLock( &ProcessCritialSection );
		UE_LOG( LogTemp , Warning , TEXT( "Start TryCancelAction , instance=%d" ), &ProcessCritialSection );
		TryCancelAction( InputTag );
		UE_LOG( LogTemp , Warning , TEXT( "End TryCancelAction" ) );
	}
	UE_LOG( LogTemp , Warning , TEXT( "End ProcessInputTriggered" ) );
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
		FScopeLock ScopeLock( &ProcessCritialSection );

		UE_LOG( LogTemp , Warning , TEXT( "Start OnAbilityEnded with currentNode, instanxe = %d" ), &ProcessCritialSection );
		// if the Ability ended is the one associated to the current Action node
		if( CurrentGraphNode->AbilityTag == AbilitySystemComponent->GetExAbilityTagFromHandle( EndedData.AbilitySpecHandle ) )
		{
			if( !TryExecuteFollowUpAction() )
			{
				CurrentGraphNode	=	nullptr;
			}
			else
			{
				UE_LOG( LogTemp , Warning , TEXT( "next action have beeen found" ) );
			}
		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "Ability ened but not same Node !!!!!!" ) );

		}
		UE_LOG( LogTemp , Warning , TEXT( "Finish OnAbilityEnded with currentNode" ) );
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
