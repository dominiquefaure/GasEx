// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionNode_Base.h"
#include "GxActionContext.h"
#include "GameplayTagContainer.h"

//---------------------------------------------------------------------------------------------
bool UGxActionNode_Base::TryExecute( FGxActionContext& InContext , FGameplayTag InInputTag )
{
	return false;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGxActionNode_Base::TryExecuteNextAction( FGxActionContext& InContext , FGameplayTag InInputTag , TObjectPtr<UGxActionNode_Base>& OutActionNode)
{
	for( UGxActionNode_Base* Node : LinkedActions )
	{
		if( Node->TryExecute( InContext , InInputTag ) )
		{
			// we found a node that can be executed
			OutActionNode = Node;
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------
