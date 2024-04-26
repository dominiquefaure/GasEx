// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GraphEditor/Schema/GasExEdGraph_EdGraphSchema.h"

#include "GraphEditor/Nodes/GasExEdGraph_EdNodeBase.h"
#include "GraphEditor/Nodes/GasExEdGraph_EdNodeEntry.h"
#include "GraphEditor/Schema/GasExEdGraph_EdGraphSchemaAction_AddAbility.h"

#include "Core/AbilityGraph/GasExGraph.h"
#include "Core/AbilityGraph/GasExGraphNodeBase.h"
#include "Core/AbilityGraph/GasExGraphNodeEntry.h"

#define LOCTEXT_NAMESPACE "UGasExEdGraph_EdGraphSchema"

//---------------------------------------------------------------------------------------------
void UGasExEdGraph_EdGraphSchema::CreateDefaultNodesForGraph( UEdGraph& Graph ) const
{
	UGasExGraph* AbilityGraph = Cast<UGasExGraph>( Graph.GetOuter() );

	// Create the entry EdGraph node
	FGraphNodeCreator<UGasExEdGraph_EdNodeEntry> NodeCreator( Graph );
	UGasExEdGraph_EdNodeEntry* EntryEdNode = NodeCreator.CreateNode();
	NodeCreator.Finalize();
	SetNodeMetaData( EntryEdNode , FNodeMetadata::DefaultGraphNode );

	// Create runtime node for the ActionGraph
	AbilityGraph->CreateDefaultEntryNode();
	EntryEdNode->RuntimeNode	=	Cast<UGasExGraphNodeBase>(AbilityGraph->EntryNode);

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdGraph_EdGraphSchema::GetGraphContextActions( FGraphContextMenuBuilder& ContextMenuBuilder ) const
{
	Super::GetGraphContextActions( ContextMenuBuilder );

	GetNewNodesActions( ContextMenuBuilder , ContextMenuBuilder.CurrentGraph );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdGraph_EdGraphSchema::GetNewNodesActions( FGraphActionMenuBuilder& ActionMenuBuilder , const UEdGraph* CurrentGraph ) const
{
	TSharedPtr<FGasExEdGraph_EdGraphSchemaAction_AddAbility> AddAbilityAction( new FGasExEdGraph_EdGraphSchemaAction_AddAbility() );
	ActionMenuBuilder.AddAction( AddAbilityAction );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
const FPinConnectionResponse UGasExEdGraph_EdGraphSchema::CanCreateConnection( const UEdGraphPin* PinA , const UEdGraphPin* PinB ) const
{
	// Make sure the pins are not on the same node
	if( PinA->GetOwningNode() == PinB->GetOwningNode() )
	{
		return FPinConnectionResponse( CONNECT_RESPONSE_DISALLOW , LOCTEXT( "PinErrorSameNode" , "Can't connect node to itself" ) );
	}

	UGasExEdGraph_EdNodeBase* EdNode_Out = Cast<UGasExEdGraph_EdNodeBase>( PinA->GetOwningNode() );
	UGasExEdGraph_EdNodeBase* EdNode_In = Cast<UGasExEdGraph_EdNodeBase>( PinB->GetOwningNode() );

	if( EdNode_Out == nullptr || EdNode_In == nullptr )
	{
		return FPinConnectionResponse( CONNECT_RESPONSE_DISALLOW , LOCTEXT( "PinError" , "Not a valid UEGSActionGraph_EdNode" ) );
	}


	return FPinConnectionResponse( CONNECT_RESPONSE_MAKE , LOCTEXT( "PinConnect" , "Connect nodes" ) );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGasExEdGraph_EdGraphSchema::TryCreateConnection( UEdGraphPin* PinA , UEdGraphPin* PinB ) const
{

	if( Super::TryCreateConnection( PinA , PinB ) )
	{
		UGasExEdGraph_EdGraph* Graph	=	Cast<UGasExEdGraph_EdGraph>( PinA->GetOwningNode()->GetGraph() );

		Graph->OnConnectionAdded( PinA , PinB );


		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
