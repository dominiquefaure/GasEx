// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GasExEdActionGraph_EdGraph.h"


//---------------------------------------------------------------------------------------------
UGasExEdActionGraph_EdGraph::UGasExEdActionGraph_EdGraph()
{
	Schema = UGasExEdGraph_EdGraphSchema::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExEdActionGraph_EdGraph::~UGasExEdActionGraph_EdGraph()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExActionGraph* UGasExEdActionGraph_EdGraph::GetOwnerGraph() const
{
	return GetTypedOuter<UGasExActionGraph>();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionGraph_EdGraph::NotifyGraphChanged()
{
	GetOwnerGraph()->MarkPackageDirty();

	Super::NotifyGraphChanged();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionGraph_EdGraph::OnConnectionAdded(UEdGraphPin* PinA , UEdGraphPin* PinB)
{
	UGasExEdActionGraphNodeBase* EdNode_Out = Cast<UGasExEdActionGraphNodeBase>(PinA->GetOwningNode());
	UGasExEdActionGraphNodeBase* EdNode_In = Cast<UGasExEdActionGraphNodeBase>(PinB->GetOwningNode());

	UGasExActionGraph* AbilityGraph = GetOwnerGraph();
	AbilityGraph->AddLink(EdNode_Out->RuntimeNode , EdNode_In->RuntimeNode);

	NotifyGraphChanged();
}
//---------------------------------------------------------------------------------------------
