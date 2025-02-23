// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ComboGraph/GxEdComboGraphUtils.h"

#include "Combos/GxComboGroup.h"
#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeBase.h"

//---------------------------------------------------------------------------------------------
UEdGraphNode* FGxEdComboGraphUtils::CreateNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode , const UClass* EdNodeClass , const UClass* RuntimeClass )
{
	UGxEdComboGraph_EdNodeBase* NewGraphNode	=	NewObject<UGxEdComboGraph_EdNodeBase>(ParentGraph , EdNodeClass , NAME_None , RF_Transactional);

	ParentGraph->Modify();
	if( FromPin )
	{
		FromPin->Modify();
	}

	// register to the graph
	NewGraphNode->CreateNewGuid();
	ParentGraph->AddNode( NewGraphNode , true , true );

	// Get the ActionGraph
	UGxComboGroup* Group					= Cast<UGxComboGroup>( ParentGraph->GetOuter() );

	NewGraphNode->RuntimeNode				=	Group->CreateNode( RuntimeClass );

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
