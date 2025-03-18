// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeNext.h"


//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdNodeNext::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin( EGPD_Input , TEXT( "Entry_Transition" ) , TEXT( "In" ) );
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
