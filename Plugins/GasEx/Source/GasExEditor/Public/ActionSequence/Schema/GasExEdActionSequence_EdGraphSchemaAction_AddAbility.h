// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "GasExEdActionSequence_EdGraphSchemaAction_AddAbility.generated.h"


/** Action to add a node to the graph */
USTRUCT()
struct FGasExEdActionSequence_EdGraphSchemaAction_AddAbility : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	FGasExEdActionSequence_EdGraphSchemaAction_AddAbility();

	virtual UEdGraphNode* PerformAction( class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2D Location , bool bSelectNewNode = true ) override;
	//	virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;

};
