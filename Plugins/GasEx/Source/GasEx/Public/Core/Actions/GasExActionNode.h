// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Abilities/GameplayAbility.h"


#include "GasExActionNode.generated.h"


class UGasExActionNodeFollowUp;
class UGasExActionNodeCancel;

/**
 * 
 */
UCLASS()
class GASEX_API UGasExActionNode : public UObject
{
	GENERATED_BODY()

public:

	// The Gameplay tag that identify The required input
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag InputTag;


	// The Gameplay tag that identify this Ability to play
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag AbilityTag;

	// Actions that can be launched once this one is finished
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TArray<UGasExActionNodeFollowUp*> FollowUpActions;
		
	// Actions that can cancel the current one
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TArray<UGasExActionNodeCancel*> CancelActions;

};
