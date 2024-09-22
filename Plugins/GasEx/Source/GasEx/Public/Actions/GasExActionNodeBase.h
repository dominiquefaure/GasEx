// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Abilities/GameplayAbility.h"


#include "GasExActionNodeBase.generated.h"


class UGasExActionNodeLink;


/**
 * 
 */
UCLASS()
class GASEX_API UGasExActionNodeBase : public UObject
{
	GENERATED_BODY()

public:

	// The Gameplay tag that identify The required input
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag InputTag;

	// The Gameplay tag that identify this Ability to play
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityTag;

	// Actions that can Launch from the current one
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<UGasExActionNodeBase*> NextActions;

};
