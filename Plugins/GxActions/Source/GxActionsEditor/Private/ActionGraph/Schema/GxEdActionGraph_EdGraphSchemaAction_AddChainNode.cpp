// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddChainNode.h"

#include "ActionGraph/GxActionNode_ChainAction.h"
#include "ActionGraph/GxEdActionGraphUtils.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeChain.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdActionGraph_EdGraphSchemaAction_AddChainNode::FGxEdActionGraph_EdGraphSchemaAction_AddChainNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Chain Action") , FText::FromString("Add a new Chain Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdActionGraph_EdGraphSchemaAction_AddChainNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddChainAction" , "Add Chain Action"));

	UGxActionNode_Base* Node	=	FGxEdActionGraphUtils::CreateRuntimeNode( ParentGraph , UGxActionNode_ChainAction::StaticClass() );
	UEdGraphNode* NewGraphNode =	FGxEdActionGraphUtils::CreateEditorNode( ParentGraph , FromPin , UGxEdActionGraph_EdNodeChain::StaticClass() , Node , Location , bSelectNewNode);

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
