// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"

#include "GxActionGroup.generated.h"

class UGxActionNode_Base;
class UGxActionNode_StartAction;
struct FGxActionContext;

/**
 * 
 */
UCLASS(Blueprintable)
class GXACTIONS_API UGxActionGroup : public UObject
{
	GENERATED_BODY()

public:

	/*
	* Holds all nodes defined for this group
	*/
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Actions")
	TArray<TObjectPtr<UGxActionNode_Base>> AllNodes;
	
	/*
	* Get all the Start nodes defined in the Graph
	* @return an array of all the start nodes
	*/
	UFUNCTION()
	TArray<UGxActionNode_StartAction*> GetAllStartNodes();


#if WITH_EDITORONLY_DATA

	/** EdGraph based representation of the Graph */
	UPROPERTY()
	TObjectPtr<class UEdGraph> EdGraph;

#endif

// Functions
public:

	/*
	* Try to start an Action 
	*/
	bool TryStartAction( FGxActionContext& InContext , FGameplayTag InInputTag, TObjectPtr<UGxActionNode_Base>& OutActionNode );



#if WITH_EDITOR

	UGxActionNode_StartAction* CreateStartNode();

	UGxActionNode_Base* CreateNode( const UClass* NodeClass );

	// Add a link between 2 nodes
	void AddLink( UGxActionNode_Base* OutputNode , UGxActionNode_Base* InputNode);

#endif


};
