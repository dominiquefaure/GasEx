// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "Actions/GasExActionSequence.h"


#if WITH_EDITOR

/*
//---------------------------------------------------------------------------------------------
UGasExActionNode* UGasExActionGraph::CreateNode( const EGasExActionNodeType ActionType )
{

	UGasExActionNode* NewNode	=	NewObject<UGasExActionNode>( this , UGasExActionNode::StaticClass() , NAME_None , RF_Transactional );
	NewNode->ActionType			=	ActionType;

	AllNodes.Add( NewNode );

	return NewNode;
}
//---------------------------------------------------------------------------------------------
*/
//---------------------------------------------------------------------------------------------
UGasExActionNodeBase* UGasExActionSequence::CreateNode( const UClass* NodeClass )
{
	UGasExActionNodeBase* NewNode = NewObject<UGasExActionNodeBase>( this , NodeClass , NAME_None , RF_Transactional );

	AllNodes.Add( NewNode );

	return NewNode;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExActionNodeStart* UGasExActionSequence::CreateStartNode()
{
	UGasExActionNodeStart* Entry = NewObject<UGasExActionNodeStart>( this , UGasExActionNodeStart::StaticClass() , NAME_None , RF_Transactional );

	AllNodes.Add( Entry );

	StartNode	=	Entry;

	return Entry;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionSequence::AddLink( UGasExActionNodeBase* SourceNode , UGasExActionNodeBase* TargetNode )
{
/*	// check link doesn't exist
	for( auto Link : SourceNode->Links )
	{
		if( Link->TargetNode == TargetNode )
		{
			return nullptr;
		}
	}

	// create a new Link
	UGasExActionNodeLink* NewLink	=	NewObject<UGasExActionNodeLink>( this , UGasExActionNodeLink::StaticClass() , NAME_None , RF_Transactional );
	NewLink->SourceNode		=	SourceNode;
	NewLink->TargetNode		=	TargetNode;

	SourceNode->Links.Add( NewLink );

	return NewLink;
*/

	if( ! SourceNode->NextActions.Contains( TargetNode ) )
	{
		SourceNode->NextActions.Add( TargetNode );
	}
}
//---------------------------------------------------------------------------------------------


#endif


