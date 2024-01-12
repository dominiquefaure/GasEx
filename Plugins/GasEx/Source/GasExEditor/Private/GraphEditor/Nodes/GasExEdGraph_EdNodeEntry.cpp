// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GraphEditor/Nodes/GasExEdGraph_EdNodeEntry.h"

//---------------------------------------------------------------------------------------------
void UGasExEdGraph_EdNodeEntry::AllocateDefaultPins()
{
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
