// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionGroup.h"
#include "ActionGraph/GxActionNode_Base.h"
#include "ActionGraph/GxActionNode_StartAction.h"

#if WITH_EDITOR

//---------------------------------------------------------------------------------------------
UGxActionNode_Base* UGxActionGroup::CreateNode( const UClass* NodeClass )
{
	UGxActionNode_Base* NewNode = NewObject<UGxActionNode_Base>( this , NodeClass , NAME_None , RF_Transactional );

	AllNodes.Add( NewNode );

	return NewNode;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGxActionNode_StartAction* UGxActionGroup::CreateStartNode()
{
	UGxActionNode_StartAction* NewNode = NewObject<UGxActionNode_StartAction>( this , UGxActionNode_StartAction::StaticClass() , NAME_None , RF_Transactional);

	AllNodes.Add( NewNode );

	return NewNode;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TArray<UGxActionNode_StartAction*> UGxActionGroup::GetAllStartNodes()
{
	TArray<UGxActionNode_StartAction*> StartNodes;

	for( UGxActionNode_Base* Node : AllNodes )
	{
		if( Node->IsA<UGxActionNode_StartAction>() )
		{
			StartNodes.Add( Cast<UGxActionNode_StartAction>(Node) );

		}
	}

	return StartNodes;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxActionGroup::AddLink( UGxActionNode_Base* SourceNode , UGxActionNode_Base* TargetNode )
{

	if( !SourceNode->LinkedActions.Contains(TargetNode) )
	{
		SourceNode->LinkedActions.Add( TargetNode );
	}

}
//---------------------------------------------------------------------------------------------


#endif