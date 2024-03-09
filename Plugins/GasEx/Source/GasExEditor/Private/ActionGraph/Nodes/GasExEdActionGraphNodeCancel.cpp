// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Nodes/GasExEdActionGraphNodeCancel.h"


//---------------------------------------------------------------------------------------------
void UGasExEdActionGraphNodeCancel::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin( EGPD_Input , TEXT( "Entry_Transition" ) , TEXT( "In" ) );
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
