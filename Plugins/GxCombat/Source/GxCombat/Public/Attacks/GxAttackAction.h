// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"

#include "GxAttackAction.generated.h"

class UGxGameplayAbility;

UENUM()
enum class EGxNextAttackType : uint8
{
	Finished		=	0 , // The Attack will try to trigger when the Previous one have finished
	Always			=	1 , // Can cancel the previous Attack at any time
	CancelWindow	=	2 , // Can cancel the Previous Attack only during the specified Cancel Window
};


/* define an Attack ( FollowUp or Cancel) that can be launched from the current one*/
USTRUCT(BlueprintType)
struct FGxNextAttack
{
	GENERATED_BODY()


	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EGxNextAttackType Type;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FString CancelWindowName;

	/* Tag to identify the possible attach to launch */
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTagContainer FollowupAttacks;

};


USTRUCT( BlueprintType )
struct FAttackDefinition : public FTableRowBase
{
	GENERATED_BODY()

	/* The gameplay tag that identify this Attack*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityTag;

	// Gameplay ability that represent the Attack to do.
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TSubclassOf<UGxGameplayAbility> Ability = nullptr;

	/* List the Differen attacks that can be launched from this one, either as follow-up or Cancel*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<FGxNextAttack> NextAttacks;

};


/**
 *
 */
UCLASS()
class UGxAttackAction : public UObject
{
	GENERATED_BODY()

public:

	/* The gameplay tag that identify this Attack*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityTag;

	// Gameplay ability that represent the Attack to do.
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TSubclassOf<UGxGameplayAbility> Ability = nullptr;

	/* List the Differen attacks that can be launched from this one, either as follow-up or Cancel*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TArray<FGxNextAttack> NextAttacks;

	// the Ability spec register to the AbilitySystemComponent
	FGameplayAbilitySpec AbilitySpec;

};