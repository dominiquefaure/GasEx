// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GxActionNode_Base.generated.h"

/**
 * 
 */
UCLASS()
class GXACTIONS_API UGxActionNode_Base : public UObject
{
	GENERATED_BODY()

public:

	/*
	* The Gameplay tag that identify The required input
	*/ 
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag InputTag;

	/*
	* The Gameplay tag that identify The action
	*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag ActionTag;

	/*
	* List of possible actions that can start from this one
	*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<TObjectPtr<UGxActionNode_Base>> LinkedActions;
};
