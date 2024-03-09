// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Schema/GasExEdActionGraph_EdGraphSchemaAction_AddFollowUpAction.h"

#include "Core/Actions/GasExActionNodeFollowUp.h"
#include "ActionGraph/GasExEdActionGraphUtils.h"

#define LOCTEXT_NAMESPACE "FGasExEdActionGraph_EdGraphSchemaAction"

//---------------------------------------------------------------------------------------------
FGasExEdActionGraph_EdGraphSchemaAction_AddFollowUpAction::FGasExEdActionGraph_EdGraphSchemaAction_AddFollowUpAction()
	:FEdGraphSchemaAction(FText::FromString("Nodes") , FText::FromString("Add Follow up Action") , FText::FromString("Add a new Follow up Action") , 0)
{

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionGraph_EdGraphSchemaAction_AddFollowUpAction::PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode)
{
	const FScopedTransaction Transaction(LOCTEXT("AddFollowUpAction" , "Add FollowUp Action"));

	UEdGraphNode* NewGraphNode = FGasExEdActionGraphUtils::CreateNode(ParentGraph , FromPin , Location , bSelectNewNode , UGasExEdActionGraphNodeFollowUp::StaticClass() , UGasExActionNodeFollowUp::StaticClass());

	return NewGraphNode;

	return nullptr;
}
//---------------------------------------------------------------------------------------------


#undef LOCTEXT_NAMESPACE
