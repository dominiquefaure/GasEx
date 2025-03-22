// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionGraphInstance.h"
#include "GxAbilitySystemComponent.h"
#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxActionNode_Base.h"
#include "ActionGraph/GxActionNode_StartAction.h"


//---------------------------------------------------------------------------------------------
UGxActionGraphInstance::UGxActionGraphInstance()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::SetAbilitySystem(UGxAbilitySystemComponent* InAbilitySystem)
{
	AbilitySystemComponent = InAbilitySystem;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::SetGraph(UGxActionGraph* InGraph)
{
	Graph				=	InGraph;
	CurrentGraphNode	=	nullptr;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::Tick( FGxActionContext& ExecutionContext )
{
	if( Graph == nullptr )
	{
		return;
	}
	ProcessWaitingState( ExecutionContext );

/*
	switch( ExecutionContext.CurrentState )
	{
		case EGxActionState::NoAction:
			ProcessWaitingState( ExecutionContext );
		break;

		case EGxActionState::ActionInProgres:
			ProcessInProgressState();
		break;

		case EGxActionState::ActionFinished:
			ProcessFinishedState();
		break;
	}
*/
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::OnInputTriggered( FGameplayTag InputTag )
{
	InputQueue.Enqueue( InputTag );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::OnCancelWindowStart( FString WindowName )
{
	IsCancelWindowsActive	=	true;
	CancelWindows.Add( WindowName );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::OnCancelWindowEnd( FString WindowName )
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
void UGxActionGraphInstance::OnAbilityEnded( const FAbilityEndedData& EndedData )
{
	if( CurrentGraphNode != nullptr )
	{
		// if the Ability ended is the one associated to the current Action node
/*		if( CurrentGraphNode->AbilityTag == AbilitySystemComponent->GetExAbilityTagFromHandle(EndedData.AbilitySpecHandle) )
		{
			CurrentState	=	EGasExActionGraphState::ActionFinished;

		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "Ability ened but not same Node !!!!!!" ) );
		}
*/
	}
}
//---------------------------------------------------------------------------------------------


//////
// Graph states process functions
/////

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::ProcessWaitingState( FGxActionContext& ExecutionContext )
{
	FGameplayTag InputTag;
	if( InputQueue.Dequeue(InputTag) )
	{
		Graph->TryStartAction( ExecutionContext , InputTag );

/*		TArray<UGxActionNode_StartAction*>	StartActions	=	Graph->GetAllStartActions();

		for( UGxActionNode_StartAction* StartNode : StartActions )
		{
			if( canExecuteAction( StartNode , InputTag ) )
			{
				ExecuteAction( StartNode );
			}
		}
*/	}

	
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::ProcessInProgressState()
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::ProcessFinishedState()
{

}
//---------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------
bool UGxActionGraphInstance::TryExecuteAction( UGxActionNode_Base* InActionNode )
{
	//todo cancel current node
/*
	if( AbilitySystemComponent != nullptr )
	{
		if( CurrentGraphNode != nullptr )
		{

		}

		// use default method as fallback
		FGameplayTagContainer Container;
		Container.AddTag( InActionNode->AbilityTag );

		if( AbilitySystemComponent->TryActivateAbilitiesByTag( Container ) )
		{
			CurrentGraphNode		=	InActionNode;
			CurrentState			=	EGxActionGraphState::ActionInProgres;

			return true;
		}
	}
*/
	return false;
}
//---------------------------------------------------------------------------------------------
