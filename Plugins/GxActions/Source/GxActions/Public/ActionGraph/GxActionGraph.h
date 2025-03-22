// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "GxActionGraph.generated.h"

struct FGxActionContext;
class UGxActionGroup;

/**
 * 
 */
UCLASS(Blueprintable)
class GXACTIONS_API UGxActionGraph : public UObject
{
	GENERATED_BODY()


// Properties
public:

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Sequences" )
	TArray<TObjectPtr<UGxActionGroup>> Groups;




#if WITH_EDITOR

	/* called by the editor when creating this asset*/
	void CreateDefaultGroup();

#endif

// Functions
public:

	/*
	* Try to start an Action 
	*/
	bool TryStartAction( FGxActionContext& InContext , FGameplayTag InInputTag );


};