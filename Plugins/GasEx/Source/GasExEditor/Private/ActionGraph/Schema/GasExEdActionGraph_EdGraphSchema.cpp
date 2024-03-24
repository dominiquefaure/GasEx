// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchema.h"


#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchemaAction_AddStartAction.h"
#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchemaAction_AddChainAction.h"


#define LOCTEXT_NAMESPACE "UGasExEdActionGraph_EdGraphSchema"

//---------------------------------------------------------------------------------------------
void UGasExEdActionGraph_EdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGasExEdActionGraph_EdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	GetNewNodesActions(ContextMenuBuilder , ContextMenuBuilder.CurrentGraph);
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionGraph_EdGraphSchema::GetNewNodesActions(FGraphActionMenuBuilder& ActionMenuBuilder , const UEdGraph* CurrentGraph) const
{
	TSharedPtr<FGasExEdActionGraph_EdGraphSchemaAction_AddStartAction> AddStartAction(new FGasExEdActionGraph_EdGraphSchemaAction_AddStartAction());
	ActionMenuBuilder.AddAction(AddStartAction);

	TSharedPtr<FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction> AddChainAction( new FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction() );
	ActionMenuBuilder.AddAction( AddChainAction );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
const FPinConnectionResponse UGasExEdActionGraph_EdGraphSchema::CanCreateConnection(const UEdGraphPin* PinA , const UEdGraphPin* PinB) const
{
	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW , LOCTEXT("PinErrorSameNode" , "Can't connect node to itself"));
	}

	UGasExEdActionGraphNodeBase* EdNode_Out = Cast<UGasExEdActionGraphNodeBase>(PinA->GetOwningNode());
	UGasExEdActionGraphNodeBase* EdNode_In = Cast<UGasExEdActionGraphNodeBase>(PinB->GetOwningNode());

	if (EdNode_Out == nullptr || EdNode_In == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW , LOCTEXT("PinError" , "Not a valid UEGSActionGraph_EdNode"));
	}


	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE , LOCTEXT("PinConnect" , "Connect nodes"));
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
bool UGasExEdActionGraph_EdGraphSchema::TryCreateConnection(UEdGraphPin* PinA , UEdGraphPin* PinB) const
{

	if (Super::TryCreateConnection(PinA , PinB))
	{
		UGasExEdActionGraph_EdGraph* Graph = Cast<UGasExEdActionGraph_EdGraph>(PinA->GetOwningNode()->GetGraph());

		Graph->OnConnectionAdded(PinA , PinB);


		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
