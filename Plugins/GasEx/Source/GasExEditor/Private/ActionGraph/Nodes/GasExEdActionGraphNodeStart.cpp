// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Nodes/GasExEdActionGraphNodeStart.h"

//---------------------------------------------------------------------------------------------
void UGasExEdActionGraphNodeStart::AllocateDefaultPins()
{
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
