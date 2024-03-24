// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "GasExEdActionGraph_EdGraphSchemaAction_AddChainAction.generated.h"


/** Action to add a node to the graph */
USTRUCT()
struct FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	FGasExEdActionGraph_EdGraphSchemaAction_AddChainAction();

	virtual UEdGraphNode* PerformAction( class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode = true ) override;
	//	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

};
