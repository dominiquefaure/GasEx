// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/Actions/GasExActionGraph.h"

#include "Core/Actions/GasExActionNodeCancel.h"
#include "Core/Actions/GasExActionNodeFollowUp.h"
#include "Core/Actions/GasExActionNodeStart.h"


//---------------------------------------------------------------------------------------------
TArray<UGasExActionNodeStart*> UGasExActionGraph::GetAllStartActions()
{
	TArray<UGasExActionNodeStart*> StartNodes;

	for( UGasExActionNode* Node : AllNodes )
	{
		UGasExActionNodeStart* StartNode	=	Cast< UGasExActionNodeStart>( Node );

		if( StartNode != nullptr )
		{
			StartNodes.Add( StartNode );
		}
	}

	return StartNodes;
}
//---------------------------------------------------------------------------------------------

#if WITH_EDITOR

//---------------------------------------------------------------------------------------------
UGasExActionNode* UGasExActionGraph::CreateNode(const UClass* NodeClass)
{
	UGasExActionNode* NewNode = NewObject<UGasExActionNode>(this , NodeClass , NAME_None , RF_Transactional);

	AllNodes.Add(NewNode);

	return NewNode;

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UGasExActionGraph::AddLink(UGasExActionNode* OutputNode , UGasExActionNode* InputNode)
{
	UGasExActionNodeFollowUp* FollowUp = Cast<UGasExActionNodeFollowUp>(InputNode );

	if( FollowUp )
	{
		OutputNode->FollowUpActions.Add( FollowUp );
	}
	else 
	{
		UGasExActionNodeCancel* Cancel = Cast<UGasExActionNodeCancel>(InputNode);
		OutputNode->CancelActions.Add( Cancel );

	}

}
//---------------------------------------------------------------------------------------------

#endif