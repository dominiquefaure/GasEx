// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionNode_AbilityAction.h"
#include "GxActionContext.h"


//---------------------------------------------------------------------------------------------
bool UGxActionNode_AbilityAction::TryExecute( FGxActionContext& InContext , FGameplayTag InInputTag )
{
	// evaluate if Tag matches
	if( InputTag != FGameplayTag::EmptyTag )
	{
		if( !InInputTag.MatchesTag( InputTag ) )
		{
			return false;
		}
	}
	else
	{
		if( InInputTag != FGameplayTag::EmptyTag )
		{
			return false;
		}
	}

	return InContext.ExecuteAction( AbilityTag );
}
//---------------------------------------------------------------------------------------------
