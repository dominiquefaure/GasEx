// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionSequence/Schema/GasExEdActionSequence_EdGraphSchemaAction_AddAbility.h"

#include "ActionSequence/GasExEdActionSequenceUtils.h"

#include "Actions/GasExActionNodeChained.h"
#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeAbility.h"



#define LOCTEXT_NAMESPACE "FGasExEdActionSequence_EdGraphSchemaAction_AddAbility"


//---------------------------------------------------------------------------------------------
FGasExEdActionSequence_EdGraphSchemaAction_AddAbility::FGasExEdActionSequence_EdGraphSchemaAction_AddAbility()
	:FEdGraphSchemaAction( FText::FromString( "Nodes" ) , FText::FromString( "Add Ability Action" ) , FText::FromString( "Add a new Action that use an Ability" ) , 0 )
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionSequence_EdGraphSchemaAction_AddAbility::PerformAction( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode )
{
	const FScopedTransaction Transaction( LOCTEXT( "AddAbility" , "Add Ability" ) );

	UEdGraphNode* NewGraphNode =	FGasExEdActionSequenceUtils::CreateNode( ParentGraph , FromPin , Location , bSelectNewNode , UGasExEdActionSequence_EdNodeAbility::StaticClass() , UGasExActionNodeChained::StaticClass() );

	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
