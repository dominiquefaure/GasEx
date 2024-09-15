// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionSequence/GasExEdActionSequenceUtils.h"

//#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeBase.h"
#include "Actions/GasExActionSequence.h"


//---------------------------------------------------------------------------------------------
UEdGraphNode* FGasExEdActionSequenceUtils::CreateNode( UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , const bool bSelectNewNode , const UClass* EdNodeClass , const UClass* RuntimeClass )
{
	UGasExEdActionSequence_EdNodeBase* NewGraphNode	=	NewObject<UGasExEdActionSequence_EdNodeBase>(ParentGraph , EdNodeClass , NAME_None , RF_Transactional);

	ParentGraph->Modify();
	if( FromPin )
	{
		FromPin->Modify();
	}

	// register to the graph
	NewGraphNode->CreateNewGuid();
	ParentGraph->AddNode( NewGraphNode , true , true );

	// Get the ActionGraph
	UGasExActionSequence* ActionSequence	= Cast<UGasExActionSequence>( ParentGraph->GetOuter() );

	NewGraphNode->RuntimeNode				=	ActionSequence->CreateNode( RuntimeClass );

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
