// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionSequence/Nodes/GasExEdActionSequence_EdNodeEntry.h"

//---------------------------------------------------------------------------------------------
void UGasExEdActionSequence_EdNodeEntry::AllocateDefaultPins()
{
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
