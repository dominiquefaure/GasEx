// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "ActionGraph/GxActionGraph.h"
#include "ActionGraph/GxActionGroup.h"

//---------------------------------------------------------------------------------------------
void UGxActionGraph::CreateDefaultGroup()
{
	UGxActionGroup* NewGroup = NewObject<UGxActionGroup>( this , UGxActionGroup::StaticClass() , NAME_None , RF_Transactional);

	Groups.Add( NewGroup );

}
//---------------------------------------------------------------------------------------------
