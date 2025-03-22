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



//////
// Graph states process functions
/////

//---------------------------------------------------------------------------------------------
void UGxActionGraphInstance::TryStartAction( FGxActionContext& ExecutionContext )
{
	if( Graph == nullptr )
	{
		return;
	}

	FGameplayTag InputTag;
	if( InputQueue.Dequeue(InputTag) )
	{
		Graph->TryStartAction( ExecutionContext , InputTag );
	}

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



