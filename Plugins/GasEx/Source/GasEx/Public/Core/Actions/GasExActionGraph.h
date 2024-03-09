// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasExActionGraph.generated.h"

class UGasExActionNode;
class UGasExActionNodeStart;

/**
 * 
 */
UCLASS(Blueprintable)
class GASEX_API UGasExActionGraph : public UObject
{
	GENERATED_BODY()

public:

	/** Holds all the Start Action nodes defined for this graph */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Action Graph")
	TArray<TObjectPtr<UGasExActionNodeStart>> StartNodes;

	/** Holds all nodes defined for this graph */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Action Graph")
	TArray<TObjectPtr<UGasExActionNode>> AllNodes;



#if WITH_EDITORONLY_DATA

	/** EdGraph based representation of the Graph */
	UPROPERTY()
	TObjectPtr<class UEdGraph> EdGraph;

#endif

#if WITH_EDITOR

	UGasExActionNode* CreateNode(const UClass* NodeClass);

	// Add a link between 2 nodes
	void AddLink(UGasExActionNode* OutputNode , UGasExActionNode* InputNode);

#endif


};
