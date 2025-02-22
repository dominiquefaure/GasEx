// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "Combos/GxComboGraph.h"


//---------------------------------------------------------------------------------------------
void UGxComboGraph::CreateDefaultGroup()
{
	UGxComboGroup* NewGroup = NewObject<UGxComboGroup>( this , UGxComboGroup::StaticClass() , NAME_None , RF_Transactional);

	Groups.Add( NewGroup );

}
//---------------------------------------------------------------------------------------------
