// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "GxEdComboGraph_EdGraphSchemaAction_AddChainNode.generated.h"


/** Action to add a node to the graph */
USTRUCT()
struct FGxEdComboGraph_EdGraphSchemaAction_AddChainNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	FGxEdComboGraph_EdGraphSchemaAction_AddChainNode();

	virtual UEdGraphNode* PerformAction( class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode = true ) override;
	//	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

};
