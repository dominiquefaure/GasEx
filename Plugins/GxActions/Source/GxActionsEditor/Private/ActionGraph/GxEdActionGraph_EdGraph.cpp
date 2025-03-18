// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxEdActionGraph_EdGraph.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeBase.h"
#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchema.h"

#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxActionGroup.h"

//---------------------------------------------------------------------------------------------
UGxEdActionGraph_EdGraph::UGxEdActionGraph_EdGraph()
{
	Schema = UGxEdActionGraph_EdGraphSchema::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGxEdActionGraph_EdGraph::~UGxEdActionGraph_EdGraph()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGxActionGroup* UGxEdActionGraph_EdGraph::GetOwnerGraph() const
{
	return GetTypedOuter<UGxActionGroup>();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdGraph::NotifyGraphChanged()
{
	UGxActionGroup* Group	=	GetOwnerGraph();

	if( Group != nullptr )
	{
		Group->MarkPackageDirty();
		Super::NotifyGraphChanged();
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdGraph::OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB )
{
	UGxEdActionGraph_EdNodeBase* EdNode_Out	=	Cast<UGxEdActionGraph_EdNodeBase>(PinA->GetOwningNode());
	UGxEdActionGraph_EdNodeBase* EdNode_In	=	Cast<UGxEdActionGraph_EdNodeBase>( PinB->GetOwningNode() );

	UGxActionGroup* ActionGraph				=	GetOwnerGraph();
	ActionGraph->AddLink( EdNode_Out->RuntimeNode , EdNode_In->RuntimeNode );

	NotifyGraphChanged();
}
//---------------------------------------------------------------------------------------------
