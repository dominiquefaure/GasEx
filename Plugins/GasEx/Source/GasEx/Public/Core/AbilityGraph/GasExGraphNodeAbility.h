// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilityGraph/GasExGraphNodeBase.h"

#include "GasExGraphNodeAbility.generated.h"

class UEGSGameplayAbility;
class UEGSAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GASEX_API UGasExGraphNodeAbility : public UGasExGraphNodeBase
{
	GENERATED_BODY()
	
public:

	// The Gameplay tag that identify this Ability to play
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityTag;


};
