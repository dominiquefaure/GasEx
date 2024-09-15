// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionSequence/Schema/GasExEdActionSequence_EdGraphSchema.h"

#include "ActionSequence/GasExEdActionSequence_EdGraph.h"
#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeBase.h"
#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeEntry.h"
#include "ActionSequence/Schema/GasExEdActionSequence_EdGraphSchemaAction_AddAbility.h"

#include "Actions/GasExActionSequence.h"
#include "Actions/GasExActionNodeBase.h"
#include "Actions/GasExActionNodeEntry.h"

#define LOCTEXT_NAMESPACE "UGasExEdGraph_EdGraphSchema"

//---------------------------------------------------------------------------------------------
void UGasExEdActionSequence_EdGraphSchema::CreateDefaultNodesForGraph( UEdGraph& Graph ) const
{
	UGasExActionSequence* AbilityGraph = Cast<UGasExActionSequence>( Graph.GetOuter() );

	// Create the entry EdGraph node
	FGraphNodeCreator<UGasExEdActionSequence_EdNodeEntry> NodeCreator( Graph );
	UGasExEdActionSequence_EdNodeEntry* EntryEdNode = NodeCreator.CreateNode();
	NodeCreator.Finalize();
	SetNodeMetaData( EntryEdNode , FNodeMetadata::DefaultGraphNode );

	// Create runtime node for the ActionGraph
	AbilityGraph->CreateDefaultEntryNode();
	EntryEdNode->RuntimeNode	=	Cast<UGasExActionNodeBase>( AbilityGraph->EntryNode );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionSequence_EdGraphSchema::GetGraphContextActions( FGraphContextMenuBuilder& ContextMenuBuilder ) const
{
	Super::GetGraphContextActions( ContextMenuBuilder );

	GetNewNodesActions( ContextMenuBuilder , ContextMenuBuilder.CurrentGraph );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionSequence_EdGraphSchema::GetNewNodesActions( FGraphActionMenuBuilder& ActionMenuBuilder , const UEdGraph* CurrentGraph ) const
{
	TSharedPtr<FGasExEdActionSequence_EdGraphSchemaAction_AddAbility> AddAbilityAction( new FGasExEdActionSequence_EdGraphSchemaAction_AddAbility() );
	ActionMenuBuilder.AddAction( AddAbilityAction );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
const FPinConnectionResponse UGasExEdActionSequence_EdGraphSchema::CanCreateConnection( const UEdGraphPin* PinA , const UEdGraphPin* PinB ) const
{
	// Make sure the pins are not on the same node
	if( PinA->GetOwningNode() == PinB->GetOwningNode() )
	{
		return FPinConnectionResponse( CONNECT_RESPONSE_DISALLOW , LOCTEXT( "PinErrorSameNode" , "Can't connect node to itself" ) );
	}

	UGasExEdActionSequence_EdNodeBase* EdNode_Out = Cast<UGasExEdActionSequence_EdNodeBase>( PinA->GetOwningNode() );
	UGasExEdActionSequence_EdNodeBase* EdNode_In = Cast<UGasExEdActionSequence_EdNodeBase>( PinB->GetOwningNode() );

	if( EdNode_Out == nullptr || EdNode_In == nullptr )
	{
		return FPinConnectionResponse( CONNECT_RESPONSE_DISALLOW , LOCTEXT( "PinError" , "Not a valid UEGSActionGraph_EdNode" ) );
	}


	return FPinConnectionResponse( CONNECT_RESPONSE_MAKE , LOCTEXT( "PinConnect" , "Connect nodes" ) );
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGasExEdActionSequence_EdGraphSchema::TryCreateConnection( UEdGraphPin* PinA , UEdGraphPin* PinB ) const
{

	if( Super::TryCreateConnection( PinA , PinB ) )
	{
		UGasExEdActionSequence_EdGraph* Graph	=	Cast<UGasExEdActionSequence_EdGraph>( PinA->GetOwningNode()->GetGraph() );
		Graph->OnConnectionAdded( PinA , PinB );


		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE


