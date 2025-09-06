#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffectTypes.h"
#include "ActiveGameplayEffectHandle.h"
#include "GxAbilitySet.h"
#include "GxAbilitySetHandle.generated.h"

class UAttributeSet;

/**
 * FGxAbilitySetHandle
 *
 *	store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FGxAbilitySetHandle
{
	GENERATED_BODY()

	// the ability set this handle is for
	TObjectPtr<class UGxAbilitySet> AbilitySet = nullptr;


	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to the granted attribute sets
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;



public:

	bool operator==(const FGxAbilitySetHandle& Other) const
	{
		return AbilitySet == Other.AbilitySet;
	}

	bool operator!=(const FGxAbilitySetHandle& Other) const
	{
		return AbilitySet != Other.AbilitySet;
	}


};
