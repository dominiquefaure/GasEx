// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "Combos/GxComboGroup.h"


#if WITH_EDITOR

//---------------------------------------------------------------------------------------------
UGxComboNode_Base* UGxComboGroup::CreateNode( const UClass* NodeClass )
{
	UGxComboNode_Base* NewNode = NewObject<UGxComboNode_Base>( this , NodeClass , NAME_None , RF_Transactional );

	AllNodes.Add( NewNode );

	return NewNode;

}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
TArray<UGxComboNode_Start*> UGxComboGroup::GetAllStartNodes()
{
	TArray<UGxComboNode_Start*> StartNodes;

	for( UGxComboNode_Base* Node : AllNodes )
	{
		UGxComboNode_Start* StartNode	=	Cast< UGxComboNode_Start>( Node );
		if( StartNode )
		{
			StartNodes.Add( StartNode );

		}
	}

	return StartNodes;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UGxComboGroup::AddLink( UGxComboNode_Base* SourceNode , UGxComboNode_Base* TargetNode )
{

	if( !SourceNode->NextNodes.Contains( TargetNode ) )
	{
		SourceNode->NextNodes.Add( TargetNode );
	}
}
//---------------------------------------------------------------------------------------------


#endif