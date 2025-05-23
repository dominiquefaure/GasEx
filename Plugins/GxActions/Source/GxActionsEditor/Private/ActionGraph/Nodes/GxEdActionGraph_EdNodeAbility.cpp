// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeAbility.h"


//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdNodeAbility::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin( EGPD_Input , TEXT( "Entry_Transition" ) , TEXT( "In" ) );
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
