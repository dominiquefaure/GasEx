// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ComboGraph/GxEdComboGraph_EdGraph.h"
#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeBase.h"
#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchema.h"

#include "Combos/GxComboGraph.h"
#include "Combos/GxComboGroup.h"

//---------------------------------------------------------------------------------------------
UGxEdComboGraph_EdGraph::UGxEdComboGraph_EdGraph()
{
	Schema = UGxEdComboGraph_EdGraphSchema::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGxEdComboGraph_EdGraph::~UGxEdComboGraph_EdGraph()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGxComboGroup* UGxEdComboGraph_EdGraph::GetOwnerGraph() const
{
	return GetTypedOuter<UGxComboGroup>();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxEdComboGraph_EdGraph::NotifyGraphChanged()
{
	UGxComboGroup* Group	=	GetOwnerGraph();

	if( Group != nullptr )
	{
		Group->MarkPackageDirty();
		Super::NotifyGraphChanged();
	}

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGxEdComboGraph_EdGraph::OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB )
{
	UGxEdComboGraph_EdNodeBase* EdNode_Out	=	Cast<UGxEdComboGraph_EdNodeBase>(PinA->GetOwningNode());
	UGxEdComboGraph_EdNodeBase* EdNode_In	=	Cast<UGxEdComboGraph_EdNodeBase>( PinB->GetOwningNode() );

	UGxComboGroup* ComboGraph				=	GetOwnerGraph();
	ComboGraph->AddLink( EdNode_Out->RuntimeNode , EdNode_In->RuntimeNode );

	NotifyGraphChanged();
}
//---------------------------------------------------------------------------------------------
