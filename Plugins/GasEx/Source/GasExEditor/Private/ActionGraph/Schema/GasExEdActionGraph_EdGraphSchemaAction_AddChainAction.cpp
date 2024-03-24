// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchemaAction_AddChainAction.h"

#include "Core/Actions/GasExActionNode.h"
#include "ActionGraph/GasExEdActionGraphUtils.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction::FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Next Action") , FText::FromString("Add a new Next Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddNExtAction" , "Add Next Action"));

	UEdGraphNode* NewGraphNode = FGasExEdActionGraphUtils::CreateNode(ParentGraph , FromPin , Location , bSelectNewNode , UGasExEdActionGraphNodeChain::StaticClass() , EGasExActionNodeType::Chained );

	return NewGraphNode;


	return nullptr;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
