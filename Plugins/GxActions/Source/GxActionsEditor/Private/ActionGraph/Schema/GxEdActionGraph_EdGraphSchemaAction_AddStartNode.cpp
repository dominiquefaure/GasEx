// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddStartNode.h"

#include "ActionGraph/GxActionNode_StartAction.h"
#include "ActionGraph/GxEdActionGraphUtils.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeStart.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdActionGraph_EdGraphSchemaAction_AddStartNode::FGxEdActionGraph_EdGraphSchemaAction_AddStartNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Start Action") , FText::FromString("Add a new Start Action Node") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdActionGraph_EdGraphSchemaAction_AddStartNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddStartAction" , "Add Start Action"));

	UGxActionNode_Base* Node	=	FGxEdActionGraphUtils::CreateRuntimeNode( ParentGraph , UGxActionNode_StartAction::StaticClass() );

	UEdGraphNode* NewGraphNode =	FGxEdActionGraphUtils::CreateEditorNode( ParentGraph , FromPin , UGxEdActionGraph_EdNodeStart::StaticClass() , Node , Location , bSelectNewNode);

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
