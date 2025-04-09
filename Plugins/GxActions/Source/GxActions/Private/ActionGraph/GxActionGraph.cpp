// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxActionGroup.h"
#include "GxActionContext.h"


//---------------------------------------------------------------------------------------------
void UGxActionGraph::CreateDefaultGroup()
{
	UGxActionGroup* NewGroup = NewObject<UGxActionGroup>( this , UGxActionGroup::StaticClass() , NAME_None , RF_Transactional);

	Groups.Add( NewGroup );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGxActionGraph::TryStartAction( FGxActionContext& InContext , FGameplayTag InInputTag , TObjectPtr<UGxActionNode_Base>& OutActionNode )
{
	for( UGxActionGroup* Group : Groups )
	{
		if( Group->TryStartAction( InContext , InInputTag, OutActionNode ) )
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------------
