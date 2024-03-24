// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/Actions/GasExActionGraph.h"


//---------------------------------------------------------------------------------------------
TArray<UGasExActionNode*> UGasExActionGraph::GetAllStartActions()
{
	TArray<UGasExActionNode*> StartNodes;

	for( UGasExActionNode* Node : AllNodes )
	{
		if( Node->ActionType == EGasExActionNodeType::Start )
		{
			StartNodes.Add( Node );
		}
	}

	return StartNodes;
}
//---------------------------------------------------------------------------------------------

#if WITH_EDITOR


//---------------------------------------------------------------------------------------------
UGasExActionNode* UGasExActionGraph::CreateNode( const EGasExActionNodeType ActionType )
{

	UGasExActionNode* NewNode	=	NewObject<UGasExActionNode>( this , UGasExActionNode::StaticClass() , NAME_None , RF_Transactional);
	NewNode->ActionType			=	ActionType;

	AllNodes.Add( NewNode );

	return NewNode;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExActionNodeLink* UGasExActionGraph::AddLink(UGasExActionNode* SourceNode , UGasExActionNode* TargetNode)
{
	// check link doesn't exist
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
}
//---------------------------------------------------------------------------------------------

#endif