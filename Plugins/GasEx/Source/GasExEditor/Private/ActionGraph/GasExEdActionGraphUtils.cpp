// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GasExEdActionGraphUtils.h"
#include "ActionGraph/Nodes/GasExEdActionGraphNodeBase.h"



//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionGraphUtils::CreateNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode , const UClass* EdNodeClass , const UClass* RuntimeClass )
{
	UGasExEdActionGraphNodeBase* NewGraphNode	=	NewObject<UGasExEdActionGraphNodeBase>( ParentGraph , EdNodeClass , NAME_None , RF_Transactional );

	ParentGraph->Modify();
	if( FromPin )
	{
		FromPin->Modify();
	}

	// register to the graph
	NewGraphNode->CreateNewGuid();
	ParentGraph->AddNode( NewGraphNode , true , true );

	// Get the ActionGraph
	UGasExActionGraph* ActionGraph = Cast<UGasExActionGraph>( ParentGraph->GetOuter() );

	NewGraphNode->RuntimeNode	= ActionGraph->CreateNode( RuntimeClass );

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
