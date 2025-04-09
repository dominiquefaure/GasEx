// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxEdActionGraphUtils.h"

#include "ActionGraph/GxActionGroup.h"
#include "ActionGraph/GxActionNode_Base.h"
#include "ActionGraph/GxActionNode_StartAction.h"
#include "ActionGraph/GxActionNode_CancelAction.h"

#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeBase.h"


//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdActionGraphUtils::CreateEditorNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const UClass* EdNodeClass ,TObjectPtr<UGxActionNode_Base> InRuntimeNode ,const FVector2D Location , const bool bSelectNewNode )
{
	UGxEdActionGraph_EdNodeBase* NewGraphNode	=	NewObject<UGxEdActionGraph_EdNodeBase>(ParentGraph , EdNodeClass , NAME_None , RF_Transactional);

	ParentGraph->Modify();
	if( FromPin )
	{
		FromPin->Modify();
	}

	// register to the graph
	NewGraphNode->CreateNewGuid();
	ParentGraph->AddNode( NewGraphNode , true , true );


	NewGraphNode->RuntimeNode				=	InRuntimeNode;

	// create pins and connections
	NewGraphNode->AllocateDefaultPins();
	NewGraphNode->AutowireNewNode( FromPin );

	// set position
	NewGraphNode->NodePosX = Location.X;
	NewGraphNode->NodePosY = Location.Y;

	// call notifies
	NewGraphNode->PostPlacedNewNode();
	ParentGraph->NotifyGraphChanged();


	return NewGraphNode;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
TObjectPtr<UGxActionNode_Base> FGxEdActionGraphUtils::CreateRuntimeNode( UEdGraph* ParentGraph , const UClass* RuntimeClass )
{
	// Get the ActionGraph
	UGxActionGroup* Group = Cast<UGxActionGroup>( ParentGraph->GetOuter() );

	return Group->CreateNode( RuntimeClass );

}
//---------------------------------------------------------------------------------------------
