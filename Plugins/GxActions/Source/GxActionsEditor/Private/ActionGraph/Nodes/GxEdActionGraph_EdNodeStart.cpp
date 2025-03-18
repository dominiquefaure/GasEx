// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/Nodes/GxEdActionGraph_EdNodeStart.h"

//---------------------------------------------------------------------------------------------
void UGxEdActionGraph_EdNodeStart::AllocateDefaultPins()
{
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
