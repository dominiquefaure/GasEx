// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionNode_Base.h"
#include "GxActionContext.h"


//---------------------------------------------------------------------------------------------
bool UGxActionNode_Base::TryExecute( FGxActionContext& InContext , FGameplayTag InInputTag )
{
	if( InInputTag.MatchesTagExact( InputTag ) )
	{

		return InContext.ExecuteAction( AbilityTag );
	}

	return false;
}
//---------------------------------------------------------------------------------------------