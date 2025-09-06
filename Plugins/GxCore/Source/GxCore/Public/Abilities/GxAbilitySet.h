#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GxAbilitySet.generated.h"

class UGxAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UPrimaryDataAsset;

/**
 * FGxAbilitySet_GameplayAbility
 *
 * Defnition of a GameplayAbility to grant.
 */
USTRUCT(BlueprintType)
struct FGxAbilitySet_GameplayAbility
{
	GENERATED_BODY()

	// The Gameplay tag that identify this Ability Definition
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityID;

	// Gameplay ability to grant
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

};

/**
 * FGxAbilitySet_GameplayEffect
 *
 * Defnition of a GameplayEffect to grant.
 */
USTRUCT(BlueprintType)
struct FGxAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};


/**
 * FGxAbilitySet_AttributeSet
 *
 * Defnition of an AttributeSet to grant.
 */
USTRUCT(BlueprintType)
struct FGxAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;

};


/**
 * Primary asset for registering gameplay abilities and effects to the Ability System.
 */
UCLASS()
class GXCORE_API UGxAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()


	UGxAbilitySet():Super()
	{
	}

// Properties
public:

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FGxAbilitySet_GameplayAbility> GameplayAbilities;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FGxAbilitySet_GameplayEffect> GameplayEffects;

	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta=(TitleProperty=AttributeSet))
	TArray<FGxAbilitySet_AttributeSet> Attributes;

};