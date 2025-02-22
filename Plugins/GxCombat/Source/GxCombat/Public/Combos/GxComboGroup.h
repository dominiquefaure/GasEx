// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GxComboNode_Base.h"
#include "GxComboNode_Start.h"

#include "GxComboGroup.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class GXCOMBAT_API UGxComboGroup : public UObject
{
	GENERATED_BODY()

public:

	/** Holds all nodes defined for this group */
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Actions")
	TArray<TObjectPtr<UGxComboNode_Base>> AllNodes;
	
	// Get all the Combo Start nodes defined in the Graph
	UFUNCTION()
	TArray<UGxComboNode_Start*> GetAllStartNodes();


#if WITH_EDITORONLY_DATA

	/** EdGraph based representation of the Graph */
	UPROPERTY()
	TObjectPtr<class UEdGraph> EdGraph;

#endif

#if WITH_EDITOR

	UGxComboNode_Start* CreateStartNode();

	UGxComboNode_Base* CreateNode( const UClass* NodeClass );

	// Add a link between 2 nodes
	void AddLink( UGxComboNode_Base* OutputNode , UGxComboNode_Base* InputNode);

#endif


};
