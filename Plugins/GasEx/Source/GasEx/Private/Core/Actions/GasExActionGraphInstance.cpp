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
	switch( CurrentState )
	{
		case EGasExActionGraphState::NoAction:
			ProcessWaitingState();
		break;

		case EGasExActionGraphState::ActionInProgres:
			ProcessActionInProgressState();
		break;

		case EGasExActionGraphState::ActionFinished:
			ProcessActionFinishedState();
		break;
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
void UGasExActionGraphInstance::OnCancelWindowStart( FString WindowName )
{
	IsCancelWindowsActive	=	true;
	CancelWindows.Add( WindowName );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::OnCancelWindowEnd( FString WindowName )
{
	int32 Index	=	-1;
	for( int32 i = 0; i < CancelWindows.Num(); i++ )
	{
		if( CancelWindows[i] == WindowName )
		{
			Index	=	i;
			break;
		}
	}

	if( Index != -1 )
	{
		CancelWindows.RemoveAt( Index );

		IsCancelWindowsActive	=	CancelWindows.Num() > 0;

	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------


//////
// Graph states process functions
/////

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::ProcessWaitingState()
{
	FGameplayTag InputTag;
	if( InputQueue.Dequeue( InputTag ) )
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
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::ProcessActionInProgressState()
{
	if( CurrentGraphNode != nullptr )
	{
		FGameplayTag InputTag;
		if( InputQueue.Dequeue( InputTag ) )
		{
			for( UGasExActionNodeLink* Link : CurrentGraphNode->Links )
			{
				if( CanExecuteLinkedAction( InputTag , Link ) )
				{
					ExecuteAction( Link->TargetNode );
					break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraphInstance::ProcessActionFinishedState()
{
	UGasExActionNodeLink* FollowUpLink	=	nullptr;
	for( UGasExActionNodeLink* Link : CurrentGraphNode->Links )
	{
		if( ( Link->TargetNode != nullptr ) && ( Link->LinkType == EGasExActionLinkType::Finished ) )
		{
			// todo : evaluate conditions of execution
			FollowUpLink	=	Link;
			break;
		}
	}

	if( FollowUpLink )
	{
		UE_LOG( LogTemp , Warning , TEXT( "next action have beeen found" ) );
		ExecuteAction( FollowUpLink->TargetNode );
	}
	else
	{
		// reset the Graph in waiting state
		CurrentGraphNode	=	nullptr;
		CurrentState		=	EGasExActionGraphState::NoAction;
	}
}
//---------------------------------------------------------------------------------------------


//////
// Action evaluations methods
/////

//---------------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::CanExecuteLinkedAction( FGameplayTag InputTag , UGasExActionNodeLink* Link )
{
	if( ( Link->TargetNode != nullptr ) && ( Link->LinkType != EGasExActionLinkType::Finished ) )
	{
		// if the Link require a Cancel window
		if( Link->LinkType == EGasExActionLinkType::InputWindow )
		{
			if( !IsCancelWindowActive( Link->CancelWindow ) )
			{
				return false;
			}
		}

		if( canExecuteAction( Link->TargetNode , InputTag ) )
		{
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::canExecuteAction( UGasExActionNode* Node , FGameplayTag InputTag )
{
	if( Node->InputTag.MatchesTagExact( InputTag ) )
	{
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::IsCancelWindowActive( FString InWindowName )
{
	for( FString WindowName : CancelWindows )
	{
		if( WindowName == InWindowName )
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------


//////
// Action execution
/////

//---------------------------------------------------------------------------------------------
bool UGasExActionGraphInstance::ExecuteAction( UGasExActionNode* NewActionNode )
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
