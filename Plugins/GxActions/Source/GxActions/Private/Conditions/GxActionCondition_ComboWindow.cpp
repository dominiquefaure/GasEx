// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "Conditions/GxActionCondition_ComboWindow.h"

//---------------------------------------------------------------------------------------------
bool UGxActionCondition_ComboWindow::EvaluateCondition( const FGxActionContext& InContext ) const
{
	return InContext.IsComboWindowActive( WindowName );
}
//---------------------------------------------------------------------------------------------
