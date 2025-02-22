// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Abilities/GameplayAbility.h"


#include "GxComboNode_Base.generated.h"




/**
 * 
 */
UCLASS()
class GXCOMBAT_API UGxComboNode_Base : public UObject
{
	GENERATED_BODY()

public:

	// The Gameplay tag that identify The required input
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag InputTag;

	// The Gameplay tag that identify the Attack to play
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AttackTag;

	// next combo attack that can Launch from the current one
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<UGxComboNode_Base*> NextNodes;

};
