// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchema.h"

#include "ActionGraph/GxEdActionGraph_EdGraph.h"
#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddStartNode.h"
#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddAbilityNode.h"
#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddCancelNode.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeBase.h"

#define LOCTEXT_NAMESPACE "UGasExEdActionGraph_EdGraphSchema"

//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	GetNewNodesActions(ContextMenuBuilder , ContextMenuBuilder.CurrentGraph);
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdGraphSchema::GetNewNodesActions(FGraphActionMenuBuilder& ActionMenuBuilder , const UEdGraph* CurrentGraph) const
{
	TSharedPtr<FGxEdActionGraph_EdGraphSchemaAction_AddStartNode> AddStartAction(new FGxEdActionGraph_EdGraphSchemaAction_AddStartNode());
	ActionMenuBuilder.AddAction(AddStartAction);

	TSharedPtr<FGxEdActionGraph_EdGraphSchemaAction_AddAbilityNode> AddAbilityAction( new FGxEdActionGraph_EdGraphSchemaAction_AddAbilityNode() );
	ActionMenuBuilder.AddAction( AddAbilityAction );

	TSharedPtr<FGxEdActionGraph_EdGraphSchemaAction_AddCancelNode> AddCancelAction( new FGxEdActionGraph_EdGraphSchemaAction_AddCancelNode() );
	ActionMenuBuilder.AddAction( AddCancelAction );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
const FPinConnectionResponse UGxEdActionGraph_EdGraphSchema::CanCreateConnection(const UEdGraphPin* PinA , const UEdGraphPin* PinB) const
{
	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW , LOCTEXT("PinErrorSameNode" , "Can't connect node to itself"));
	}

	UGxEdActionGraph_EdNodeBase* EdNode_Out = Cast<UGxEdActionGraph_EdNodeBase>(PinA->GetOwningNode());
	UGxEdActionGraph_EdNodeBase* EdNode_In = Cast<UGxEdActionGraph_EdNodeBase>(PinB->GetOwningNode());

	if (EdNode_Out == nullptr || EdNode_In == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW , LOCTEXT("PinError" , "Not a valid UEGSActionGraph_EdNode"));
	}


	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE , LOCTEXT("PinConnect" , "Connect nodes"));
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGxEdActionGraph_EdGraphSchema::TryCreateConnection(UEdGraphPin* PinA , UEdGraphPin* PinB) const
{
	
	if (Super::TryCreateConnection(PinA , PinB))
	{
		UGxEdActionGraph_EdGraph* Graph = Cast<UGxEdActionGraph_EdGraph>(PinA->GetOwningNode()->GetGraph());

		Graph->OnConnectionAdded(PinA , PinB);


		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
