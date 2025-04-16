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
void UGxActionGraphInstance::SetGraph(UGxActionGraph* InGraph)
{
	Graph				=	InGraph;
	CurrentGraphNode	=	nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::OnReset()
{
	CurrentGraphNode = nullptr;
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



//////
// Graph states process functions
/////

//---------------------------------------------------------------------------------------------
bool UGxActionGraphInstance::TryStartAction( FGxActionContext& ExecutionContext , FGameplayTag InInputTag )
{
	if( Graph == nullptr )
	{
		return false;
	}

	return Graph->TryStartAction( ExecutionContext , InInputTag, CurrentGraphNode );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGxActionGraphInstance::OnActionFinished( FGxActionContext& ExecutionContext )
{
	if( CurrentGraphNode != nullptr )
	{
		return CurrentGraphNode->TryExecuteNextAction( ExecutionContext , FGameplayTag() , CurrentGraphNode );
	}

	return false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::UpdateCurrentAction( FGxActionContext& ExecutionContext )
{
	// peek the input tag
	FGameplayTag InputTag	=	ExecutionContext.GetInputTag( false );
	if( InputTag != FGameplayTag::EmptyTag )
	{
		if( CurrentGraphNode != nullptr )
		{
			// if success to trigger a next action.
			if( CurrentGraphNode->TryExecuteNextAction( ExecutionContext , InputTag , CurrentGraphNode ) )
			{
				// consume the input
				ExecutionContext.GetInputTag( true );
			}
		}
	}

}
//---------------------------------------------------------------------------------------------


