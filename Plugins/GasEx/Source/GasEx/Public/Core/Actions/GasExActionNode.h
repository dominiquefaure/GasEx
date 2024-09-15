// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Abilities/GameplayAbility.h"


#include "GasExActionNode.generated.h"


class UGasExActionNodeLink;

UENUM()
enum class EGasExActionNodeType : uint8
{
	Start	= 0 ,	// First action of a chain
	Chained	= 1 ,	// any node of the Chain
};

/**
 * 
 */
UCLASS()
class GASEX_API UGasExActionNode : public UObject
{
	GENERATED_BODY()

public:

	// Type of Action
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EGasExActionNodeType ActionType;

	// The Gameplay tag that identify The required input
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag InputTag;


	// The Gameplay tag that identify this Ability to play
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag AbilityTag;

	// Actions that can Launch from the current one
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<UGasExActionNodeLink*> Links;

};
