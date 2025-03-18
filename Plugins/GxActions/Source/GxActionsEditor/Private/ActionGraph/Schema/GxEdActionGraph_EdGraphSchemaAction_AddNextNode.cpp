// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddNextNode.h"

#include "ActionGraph/GxActionNode_NextAction.h"
#include "ActionGraph/GxEdActionGraphUtils.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeNext.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdActionGraph_EdGraphSchemaAction_AddNextNode::FGxEdActionGraph_EdGraphSchemaAction_AddNextNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Next Action") , FText::FromString("Add a new Action action that can only start once current one is finished") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdActionGraph_EdGraphSchemaAction_AddNextNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddNextAction" , "Add Next Action"));

	UGxActionNode_Base* Node	=	FGxEdActionGraphUtils::CreateRuntimeNode( ParentGraph , UGxActionNode_NextAction::StaticClass() );
	UEdGraphNode* NewGraphNode =	FGxEdActionGraphUtils::CreateEditorNode( ParentGraph , FromPin , UGxEdActionGraph_EdNodeNext::StaticClass() , Node , Location , bSelectNewNode);

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
