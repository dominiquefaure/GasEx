// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GraphEditor/GasExEdGraph_EdGraph.h"
#include "GraphEditor/Nodes/GasExEdGraph_EdNodeBase.h"
#include "GraphEditor/Schema/GasExEdGraph_EdGraphSchema.h"

#include "Core/AbilityGraph/GasExGraph.h"
#include "Core/AbilityGraph/GasExGraphLink.h"


//---------------------------------------------------------------------------------------------
UGasExEdGraph_EdGraph::UGasExEdGraph_EdGraph()
{
	Schema = UGasExEdGraph_EdGraphSchema::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExEdGraph_EdGraph::~UGasExEdGraph_EdGraph()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExGraph* UGasExEdGraph_EdGraph::GetOwnerGraph() const
{
	return GetTypedOuter<UGasExGraph>();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdGraph_EdGraph::NotifyGraphChanged()
{
	GetOwnerGraph()->MarkPackageDirty();

	Super::NotifyGraphChanged();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdGraph_EdGraph::OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB )
{
	UGasExEdGraph_EdNodeBase* EdNode_Out = Cast<UGasExEdGraph_EdNodeBase>( PinA->GetOwningNode() );
	UGasExEdGraph_EdNodeBase* EdNode_In = Cast<UGasExEdGraph_EdNodeBase>( PinB->GetOwningNode() );

	UGasExGraph* AbilityGraph = GetOwnerGraph();
	UGasExGraphLink* NewLink	=	AbilityGraph->AddLink( EdNode_Out->RuntimeNode , EdNode_In->RuntimeNode );

	NotifyGraphChanged();
}
//---------------------------------------------------------------------------------------------
