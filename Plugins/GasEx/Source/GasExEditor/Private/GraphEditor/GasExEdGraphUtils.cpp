// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GraphEditor/GasExEdGraphUtils.h"

#include "GraphEditor/Nodes/GasExEdGraph_EdNodeBase.h"
#include "Core/AbilityGraph/GasExGraph.h"


//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdGraphUtils::CreateNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode , const UClass* EdNodeClass , const UClass* RuntimeClass )
{
	UGasExEdGraph_EdNodeBase* NewGraphNode	=	NewObject<UGasExEdGraph_EdNodeBase>( ParentGraph , EdNodeClass , NAME_None , RF_Transactional );

	ParentGraph->Modify();
	if( FromPin )
	{
		FromPin->Modify();
	}

	// register to the graph
	NewGraphNode->CreateNewGuid();
	ParentGraph->AddNode( NewGraphNode , true , true );

	// Get the ActionGraph
	UGasExGraph* AbilityGraph = Cast<UGasExGraph>( ParentGraph->GetOuter() );

	NewGraphNode->RuntimeNode	=	AbilityGraph->CreateNode( RuntimeClass );

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
