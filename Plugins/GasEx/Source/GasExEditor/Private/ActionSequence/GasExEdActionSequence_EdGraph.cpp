// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionSequence/GasExEdActionSequence_EdGraph.h"
#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeBase.h"
#include "ActionSequence/Schema/GasExEdActionSequence_EdGraphSchema.h"

#include "Actions/GasExActionSequence.h"
//#include "Core/AbilityGraph/GasExGraphLink.h"


//---------------------------------------------------------------------------------------------
UGasExEdActionSequence_EdGraph::UGasExEdActionSequence_EdGraph()
{
	Schema = UGasExEdActionSequence_EdGraphSchema::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExEdActionSequence_EdGraph::~UGasExEdActionSequence_EdGraph()
{
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UGasExActionSequence* UGasExEdActionSequence_EdGraph::GetOwnerGraph() const
{
	return GetTypedOuter<UGasExActionSequence>();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionSequence_EdGraph::NotifyGraphChanged()
{
	GetOwnerGraph()->MarkPackageDirty();

	Super::NotifyGraphChanged();

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExEdActionSequence_EdGraph::OnConnectionAdded( UEdGraphPin* PinA , UEdGraphPin* PinB )
{
	UGasExEdActionSequence_EdNodeBase* EdNode_Out	=	Cast<UGasExEdActionSequence_EdNodeBase>(PinA->GetOwningNode());
	UGasExEdActionSequence_EdNodeBase* EdNode_In	=	Cast<UGasExEdActionSequence_EdNodeBase>( PinB->GetOwningNode() );

	UGasExActionSequence* ActionSequence			=	GetOwnerGraph();
	ActionSequence->AddLink( EdNode_Out->RuntimeNode , EdNode_In->RuntimeNode );

	NotifyGraphChanged();
}
//---------------------------------------------------------------------------------------------
