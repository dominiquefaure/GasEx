// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/GasExActionSequenceInstance.h"
#include "Actions/GasExActionSequence.h"
#include "Actions/GasExActionNodeBase.h"
#include "Actions/GasExActionNodeStart.h"
#include "Actions/GasExActionNodeChained.h"
#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::SetAbilitySystem(UGasExAbilitySystemComponent* InAbilitySystem)
{
	AbilitySystemComponent = InAbilitySystem;
	AbilitySystemComponent->OnAbilityEnded.AddUObject( this , &UGasExActionSequenceInstance::OnAbilityEnded );

	CurrentState	=	EGasExActionSequenceState::NoAction;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::SetSequence(UGasExActionSequence* InSequence)
{
	Sequence	=	InSequence;
	CurrentNode =	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::Tick()
{
	if( Sequence == nullptr )
	{
		return;
	}

	switch( CurrentState )
	{
		case EGasExActionSequenceState::NoAction:
			ProcessWaitingState();
		break;

		case EGasExActionSequenceState::ActionInProgres:
			ProcessActionInProgressState();
		break;

		case EGasExActionSequenceState::ActionFinished:
			ProcessActionFinishedState();
		break;
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::OnInputTriggered( FGameplayTag InputTag )
{
	InputQueue.Enqueue( InputTag );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::OnCancelWindowStart( FString WindowName )
{
	IsCancelWindowsActive	=	true;
	CancelWindows.Add( WindowName );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::OnCancelWindowEnd( FString WindowName )
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
void UGasExActionSequenceInstance::OnAbilityEnded( const FAbilityEndedData& EndedData )
{
	if( CurrentNode != nullptr )
	{
		// if the Ability ended is the one associated to the current Action node
		if( CurrentNode->AbilityTag == AbilitySystemComponent->GetExAbilityTagFromHandle( EndedData.AbilitySpecHandle ) )
		{
			CurrentState	=	EGasExActionSequenceState::ActionFinished;
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
void UGasExActionSequenceInstance::ProcessWaitingState()
{
	FGameplayTag InputTag;
	if( InputQueue.Dequeue( InputTag ) )
	{
		if( CanExecuteAction( Sequence->StartNode , InputTag ) )
		{
			ExecuteAction( Sequence->StartNode );
		}
	}
	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::ProcessActionInProgressState()
{
	if( CurrentNode != nullptr )
	{
		FGameplayTag InputTag;
		if( InputQueue.Dequeue( InputTag ) )
		{
			for( UGasExActionNodeBase* NextAction : CurrentNode->NextActions )
			{
				if( TryCancelCurrentAction( NextAction , InputTag ) )
				{
					break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequenceInstance::ProcessActionFinishedState()
{
	bool NextActonFound	=	false;

	for( UGasExActionNodeBase* NextAction : CurrentNode->NextActions )
	{
		UGasExActionNodeChained* ChainedNode	=	Cast<UGasExActionNodeChained>( NextAction );

		if( ChainedNode != nullptr )
		{
			if( ChainedNode->ChainType == EGasExActionChainType::Finished )
			{
				ExecuteAction( ChainedNode );
				NextActonFound	=	true;

				break;
			}
		}
	}
	if( NextActonFound == false )
	{
		// reset the Graph in waiting state
		CurrentNode		=	nullptr;
		CurrentState	=	EGasExActionSequenceState::NoAction;

	}
}
//---------------------------------------------------------------------------------------------


//////
// Action evaluations methods
/////

//---------------------------------------------------------------------------------------------
bool UGasExActionSequenceInstance::CanExecuteAction( UGasExActionNodeBase* Node , FGameplayTag InputTag )
{
	if( Node->InputTag.MatchesTagExact( InputTag ) )
	{
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExActionSequenceInstance::TryCancelCurrentAction( UGasExActionNodeBase* Node , FGameplayTag InputTag )
{
	UGasExActionNodeChained* ChainedNode	=	Cast<UGasExActionNodeChained>(Node);

	if( ChainedNode == nullptr )
	{
		return false;
	}

	if( ChainedNode->ChainType == EGasExActionChainType::Finished )
	{
		return false;
	}

	if( ChainedNode->ChainType == EGasExActionChainType::CancelWindow )
	{
		if( !IsCancelWindowActive( ChainedNode->CancelWindow ) )
		{
			return false;
		}
	}
	if( CanExecuteAction( ChainedNode , InputTag ) )
	{
		ExecuteAction( ChainedNode );
	}

	return false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExActionSequenceInstance::IsCancelWindowActive( FString InWindowName )
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
bool UGasExActionSequenceInstance::ExecuteAction( UGasExActionNodeBase* NewActionNode )
{
	check(AbilitySystemComponent);

	if( NewActionNode == nullptr )
	{
		return false;
	}

	if( CurrentNode != nullptr )
	{
		if( NewActionNode->AbilityTag == CurrentNode->AbilityTag )
		{
			UE_LOG( LogTemp , Warning , TEXT( "Error try to cancel an acton by itself!!!!!!!!" ) );

			return false;
		}
	}

	// if the Activation succeed, made the node the new active one
	if( AbilitySystemComponent->TryActivateExAbility( NewActionNode->AbilityTag ) )
	{
		// Cancel the current Node
		if( CurrentNode != nullptr )
		{
			FGameplayTag PreviousAbilityTag	=	CurrentNode->AbilityTag;
			CurrentNode						=	nullptr;
			AbilitySystemComponent->CancelExAbility( PreviousAbilityTag );
		}

		CurrentNode		=	NewActionNode;
		CurrentState	=	EGasExActionSequenceState::ActionInProgres;

		return true;
	}

	return false;

}
//---------------------------------------------------------------------------------------------
