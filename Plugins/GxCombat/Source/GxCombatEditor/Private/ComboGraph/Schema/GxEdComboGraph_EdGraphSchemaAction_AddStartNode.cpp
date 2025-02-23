// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchemaAction_AddStartNode.h"

#include "Combos/GxComboNode_Start.h"
#include "ComboGraph/GxEdComboGraphUtils.h"
#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeStart.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdComboGraph_EdGraphSchemaAction_AddStartNode::FGxEdComboGraph_EdGraphSchemaAction_AddStartNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Start Node") , FText::FromString("Add a new Start Combo Node") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdComboGraph_EdGraphSchemaAction_AddStartNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddStartNode" , "Add Start Node"));

	UEdGraphNode* NewGraphNode =	FGxEdComboGraphUtils::CreateNode( ParentGraph , FromPin , Location , bSelectNewNode , UGxEdComboGraph_EdNodeStart::StaticClass() , UGxComboNode_Start::StaticClass() );

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
