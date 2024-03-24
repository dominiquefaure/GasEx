// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/Actions/GasExActionNode.h"

#include "GasExActionGraph.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GASEX_API UGasExActionGraph : public UObject
{
	GENERATED_BODY()

public:


	/** Holds all nodes defined for this graph */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Action Graph")
	TArray<TObjectPtr<UGasExActionNode>> AllNodes;

	// Get all the Start Actions defined in the Graph
	UFUNCTION( )
	TArray<UGasExActionNode*> GetAllStartActions();

#if WITH_EDITORONLY_DATA

	/** EdGraph based representation of the Graph */
	UPROPERTY()
	TObjectPtr<class UEdGraph> EdGraph;

#endif

#if WITH_EDITOR

	UGasExActionNode* CreateNode( const EGasExActionNodeType ActionType );

	// Add a link between 2 nodes
	UGasExActionNodeLink* AddLink(UGasExActionNode* OutputNode , UGasExActionNode* InputNode);

#endif


};
