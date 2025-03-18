// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddCancelNode.h"

#include "ActionGraph/GxActionNode_CancelAction.h"
#include "ActionGraph/GxEdActionGraphUtils.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeCancel.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdActionGraph_EdGraphSchemaAction_AddCancelNode::FGxEdActionGraph_EdGraphSchemaAction_AddCancelNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Cancel Action") , FText::FromString("Add the possibility to cancel an Action by a new Start one") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdActionGraph_EdGraphSchemaAction_AddCancelNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddCancelAction" , "Add Cancel Action"));

	UGxActionNode_Base* Node	=	FGxEdActionGraphUtils::CreateRuntimeNode( ParentGraph ,UGxActionNode_CancelAction::StaticClass() );
	UEdGraphNode* NewGraphNode =	FGxEdActionGraphUtils::CreateEditorNode( ParentGraph , FromPin , UGxEdActionGraph_EdNodeCancel::StaticClass() , Node , Location , bSelectNewNode);

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
