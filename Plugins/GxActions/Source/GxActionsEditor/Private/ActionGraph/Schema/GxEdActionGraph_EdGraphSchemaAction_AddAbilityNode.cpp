// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GxEdActionGraph_EdGraphSchemaAction_AddAbilityNode.h"

#include "ActionGraph/GxActionNode_AbilityAction.h"
#include "ActionGraph/GxEdActionGraphUtils.h"
#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeAbility.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdActionGraph_EdGraphSchemaAction_AddAbilityNode::FGxEdActionGraph_EdGraphSchemaAction_AddAbilityNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Ability Action") , FText::FromString("Add a new Ability Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdActionGraph_EdGraphSchemaAction_AddAbilityNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddAbilityAction" , "Add Ability Action"));

	UGxActionNode_Base* Node	=	FGxEdActionGraphUtils::CreateRuntimeNode( ParentGraph , UGxActionNode_AbilityAction::StaticClass() );
	UEdGraphNode* NewGraphNode =	FGxEdActionGraphUtils::CreateEditorNode( ParentGraph , FromPin , UGxEdActionGraph_EdNodeAbility::StaticClass() , Node , Location , bSelectNewNode);

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
