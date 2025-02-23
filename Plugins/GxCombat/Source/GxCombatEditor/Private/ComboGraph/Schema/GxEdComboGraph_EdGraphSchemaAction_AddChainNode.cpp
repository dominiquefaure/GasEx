// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ComboGraph/Schema/GxEdComboGraph_EdGraphSchemaAction_AddChainNode.h"

#include "Combos/GxComboNode_Chained.h"
#include "ComboGraph/GxEdComboGraphUtils.h"
#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeChain.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGxEdComboGraph_EdGraphSchemaAction_AddChainNode::FGxEdComboGraph_EdGraphSchemaAction_AddChainNode()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Next Action") , FText::FromString("Add a new Next Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdComboGraph_EdGraphSchemaAction_AddChainNode::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddNextAction" , "Add Next Action"));

	UEdGraphNode* NewGraphNode =	FGxEdComboGraphUtils::CreateNode( ParentGraph , FromPin , Location , bSelectNewNode , UGxEdComboGraph_EdNodeChain::StaticClass() , UGxComboNode_Chained::StaticClass() );

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
