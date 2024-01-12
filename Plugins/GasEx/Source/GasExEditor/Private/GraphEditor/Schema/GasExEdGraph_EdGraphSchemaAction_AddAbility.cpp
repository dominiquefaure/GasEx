// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GraphEditor/Schema/GasExEdGraph_EdGraphSchemaAction_AddAbility.h"

#include "GraphEditor/GasExEdGraphUtils.h"

#include "Core/AbilityGraph/GasExGraphNodeAbility.h"
#include "GraphEditor/Nodes/GasExEdGraph_EdNodeAbility.h"



#define LOCTEXT_NAMESPACE "FGasExEdGraph_EdGraphSchemaAction_AddAbility"


//---------------------------------------------------------------------------------------------
FGasExEdGraph_EdGraphSchemaAction_AddAbility::FGasExEdGraph_EdGraphSchemaAction_AddAbility()
	:FEdGraphSchemaAction( FText::FromString( "Nodes" ) , FText::FromString( "Add Ability Action" ) , FText::FromString( "Add a new Action that use an Ability" ) , 0 )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdGraph_EdGraphSchemaAction_AddAbility::PerformAction( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode )
{
	const FScopedTransaction Transaction( LOCTEXT( "AddAbility" , "Add Ability" ) );

	UEdGraphNode* NewGraphNode =	FGasExEdGraphUtils::CreateNode( ParentGraph , FromPin , Location , bSelectNewNode , UGasExEdGraph_EdNodeAbility::StaticClass() , UGasExGraphNodeAbility::StaticClass() );

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
