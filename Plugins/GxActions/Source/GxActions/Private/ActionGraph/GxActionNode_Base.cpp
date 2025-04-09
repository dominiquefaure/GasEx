// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionNode_Base.h"
#include "GxActionContext.h"
#include "GameplayTagContainer.h"

//---------------------------------------------------------------------------------------------
bool UGxActionNode_Base::TryExecute( FGxActionContext& InContext , FGameplayTag InInputTag )
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

//---------------------------------------------------------------------------------------------
bool UGxActionNode_Base::TryExecuteNextAction( FGxActionContext& InContext , FGameplayTag InInputTag )
{
	for( UGxActionNode_Base* Node : LinkedActions )
	{
		if( Node->TryExecute( InContext , InInputTag ) )
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------
