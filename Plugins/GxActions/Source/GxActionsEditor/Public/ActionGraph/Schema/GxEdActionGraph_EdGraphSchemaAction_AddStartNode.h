// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "GxEdActionGraph_EdGraphSchemaAction_AddStartNode.generated.h"


/** Action to add a node to the graph */
USTRUCT()
struct FGxEdActionGraph_EdGraphSchemaAction_AddStartNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	FGxEdActionGraph_EdGraphSchemaAction_AddStartNode();

	virtual UEdGraphNode* PerformAction( class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode = true ) override;
	//	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

};
