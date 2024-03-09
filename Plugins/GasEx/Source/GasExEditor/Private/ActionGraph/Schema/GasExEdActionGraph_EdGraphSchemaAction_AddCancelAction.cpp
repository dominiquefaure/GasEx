// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchemaAction_AddCancelAction.h"

#include "Core/Actions/GasExActionNodeCancel.h"
#include "ActionGraph/GasExEdActionGraphUtils.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGasExEdActionGraph_EdGraphSchemaAction_AddCancelAction::FGasExEdActionGraph_EdGraphSchemaAction_AddCancelAction()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Cancel Action") , FText::FromString("Add a new Cancel Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionGraph_EdGraphSchemaAction_AddCancelAction::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddCancelAction" , "Add Cancel Action"));

	UEdGraphNode* NewGraphNode = FGasExEdActionGraphUtils::CreateNode(ParentGraph , FromPin , Location , bSelectNewNode , UGasExEdActionGraphNodeCancel::StaticClass() , UGasExActionNodeCancel::StaticClass());

	return nullptr;
}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
