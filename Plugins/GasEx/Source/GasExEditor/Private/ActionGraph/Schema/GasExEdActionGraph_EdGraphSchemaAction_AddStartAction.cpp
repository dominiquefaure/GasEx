// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchemaAction_AddStartAction.h"

#include "Core/Actions/GasExActionNodeStart.h"
#include "ActionGraph/GasExEdActionGraphUtils.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGasExEdActionGraph_EdGraphSchemaAction_AddStartAction::FGasExEdActionGraph_EdGraphSchemaAction_AddStartAction()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Start Action") , FText::FromString("Add a new Start Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionGraph_EdGraphSchemaAction_AddStartAction::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddStartAction" , "Add Start Action"));

	UEdGraphNode* NewGraphNode = FGasExEdActionGraphUtils::CreateNode(ParentGraph , FromPin , Location , bSelectNewNode , UGasExEdActionGraphNodeStart::StaticClass() , UGasExActionNodeStart::StaticClass());

	return NewGraphNode;


	return nullptr;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
