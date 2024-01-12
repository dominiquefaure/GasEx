// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "Core/AbilityGraph/GasExGraph.h"

//---------------------------------------------------------------------------------------------
UGasExGraphNodeEntry* UGasExGraph::CreateDefaultEntryNode()
{
	UGasExGraphNodeEntry* Entry = NewObject<UGasExGraphNodeEntry>( this , UGasExGraphNodeEntry::StaticClass() , NAME_None , RF_Transactional );

	AllNodes.Add( Entry );

	EntryNode	=	Entry;

	return Entry;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExGraphNodeBase* UGasExGraph::CreateNode( const UClass* NodeClass )
{
	UGasExGraphNodeBase* NewNode = NewObject<UGasExGraphNodeBase>( this , NodeClass , NAME_None , RF_Transactional );

	AllNodes.Add( NewNode );

	return NewNode;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExGraphLink* UGasExGraph::AddLink( UGasExGraphNodeBase* OutputNode , UGasExGraphNodeBase* InputNode )
{
	// check link doesn't exist
	for( auto Link : OutputNode->Links )
	{
		if( Link->EndNode == InputNode )
		{
			return nullptr;
		}
	}

	// create a new Link
	UGasExGraphLink* NewLink	=	NewObject<UGasExGraphLink>( this , UGasExGraphLink::StaticClass() , NAME_None , RF_Transactional );
	NewLink->StartNode		=	OutputNode;
	NewLink->EndNode		=	InputNode;

	OutputNode->Links.Add( NewLink );

	return NewLink;
}
//---------------------------------------------------------------------------------------------
