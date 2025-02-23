// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchema.h"

#include "ComboGraph/GxEdComboGraph_EdGraph.h"
#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchemaAction_AddChainNode.h"
#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchemaAction_AddStartNode.h"
#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeBase.h"

#define LOCTEXT_NAMESPACE "UGasExEdActionGraph_EdGraphSchema"

//---------------------------------------------------------------------------------------------
void UGxEdComboGraph_EdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxEdComboGraph_EdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	GetNewNodesActions(ContextMenuBuilder , ContextMenuBuilder.CurrentGraph);
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxEdComboGraph_EdGraphSchema::GetNewNodesActions(FGraphActionMenuBuilder& ActionMenuBuilder , const UEdGraph* CurrentGraph) const
{
	TSharedPtr<FGxEdComboGraph_EdGraphSchemaAction_AddStartNode> AddStartAction(new FGxEdComboGraph_EdGraphSchemaAction_AddStartNode());
	ActionMenuBuilder.AddAction(AddStartAction);

	TSharedPtr<FGxEdComboGraph_EdGraphSchemaAction_AddChainNode> AddChainAction( new FGxEdComboGraph_EdGraphSchemaAction_AddChainNode() );
	ActionMenuBuilder.AddAction( AddChainAction );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
const FPinConnectionResponse UGxEdComboGraph_EdGraphSchema::CanCreateConnection(const UEdGraphPin* PinA , const UEdGraphPin* PinB) const
{
	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW , LOCTEXT("PinErrorSameNode" , "Can't connect node to itself"));
	}

	UGxEdComboGraph_EdNodeBase* EdNode_Out = Cast<UGxEdComboGraph_EdNodeBase>(PinA->GetOwningNode());
	UGxEdComboGraph_EdNodeBase* EdNode_In = Cast<UGxEdComboGraph_EdNodeBase>(PinB->GetOwningNode());

	if (EdNode_Out == nullptr || EdNode_In == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW , LOCTEXT("PinError" , "Not a valid UEGSActionGraph_EdNode"));
	}


	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE , LOCTEXT("PinConnect" , "Connect nodes"));
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGxEdComboGraph_EdGraphSchema::TryCreateConnection(UEdGraphPin* PinA , UEdGraphPin* PinB) const
{
	
	if (Super::TryCreateConnection(PinA , PinB))
	{
		UGxEdComboGraph_EdGraph* Graph = Cast<UGxEdComboGraph_EdGraph>(PinA->GetOwningNode()->GetGraph());

		Graph->OnConnectionAdded(PinA , PinB);


		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
