// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Actions/GasExActionNodeBase.h"
#include "Actions/GasExActionNodeEntry.h"

#include "GasExActionSequence.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class GASEX_API UGasExActionSequence : public UObject
{
	GENERATED_BODY()

public:

	/** Entry node of the Sequence execution flow. */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Actions" )
	TObjectPtr<UGasExActionNodeEntry> EntryNode;

	/** Holds all nodes defined for this graph */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Actions")
	TArray<TObjectPtr<UGasExActionNodeBase>> AllNodes;


#if WITH_EDITORONLY_DATA

	/** EdGraph based representation of the Graph */
	UPROPERTY()
	TObjectPtr<class UEdGraph> EdGraph;

#endif

#if WITH_EDITOR

	UGasExActionNodeEntry* CreateDefaultEntryNode();

//	UGasExActionNodeBase* CreateNode( const EGasExActionNodeType ActionType );
	UGasExActionNodeBase* CreateNode( const UClass* NodeClass );

	// Add a link between 2 nodes
	void AddLink( UGasExActionNodeBase* OutputNode , UGasExActionNodeBase* InputNode);

#endif


};