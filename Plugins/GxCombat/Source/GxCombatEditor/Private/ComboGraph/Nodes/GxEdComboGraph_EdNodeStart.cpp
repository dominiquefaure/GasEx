// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ComboGraph/Nodes/GxEdComboGraph_EdNodeStart.h"

//---------------------------------------------------------------------------------------------
void UGxEdComboGraph_EdNodeStart::AllocateDefaultPins()
{
	UEdGraphPin* Outputs = CreatePin( EGPD_Output , TEXT( "Entry_Transition" ) , TEXT( "Out" ) );
}
//---------------------------------------------------------------------------------------------
