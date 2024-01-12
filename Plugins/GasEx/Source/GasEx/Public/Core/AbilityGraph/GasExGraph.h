// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasExGraph.generated.h"


class UGasExGraphNodeBase;
class UGasExGraphNodeEntry;
class UGasExGraphLink;

/**
 *
 */
UCLASS( Blueprintable )
class GASEX_API UGasExGraph : public UObject
{
	GENERATED_BODY()

public:

	/** Entry node of the Graph execution flow. */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Ability Graph" )
	TObjectPtr<UGasExGraphNodeEntry> EntryNode;

	/** Holds all nodes defined for this graph */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Ability Graph" )
	TArray<TObjectPtr<UGasExGraphNodeBase>> AllNodes;

	// Add a link between 2 nodes
	UGasExGraphLink* AddLink( UGasExGraphNodeBase* OutputNode , UGasExGraphNodeBase* InputNode );


public:

#if WITH_EDITORONLY_DATA

	/** EdGraph based representation of the Graph */
	UPROPERTY()
	TObjectPtr<class UEdGraph> EdGraph;

#endif

#if WITH_EDITOR
	UGasExGraphNodeEntry* CreateDefaultEntryNode();

	UGasExGraphNodeBase* CreateNode( const UClass* NodeClass );
#endif


};
