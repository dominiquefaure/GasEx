// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "Actions/GasExActionNodeBase.h"
#include "GasExActionNodeAbility.generated.h"


/**
 * 
 */
UCLASS()
class GASEX_API UGasExActionNodeAbility : public UGasExActionNodeBase
{
	GENERATED_BODY()

public:

	// The Gameplay tag that identify The required input
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag InputTag;

	// The Gameplay tag that identify this Ability to play
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag AbilityTag;

};
