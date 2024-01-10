// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"

#include "GasExAbilitySet.generated.h"


class UGasExAbilitySystemComponent;
class UGasExGameplayAbility;


USTRUCT( BlueprintType )
struct GASEX_API FGasExAbilitySetRow
{
	GENERATED_BODY()

	// The Gameplay tag that identify this Ability Definition
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGameplayTag AbilityTag;

	// Gameplay ability to grant.
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TSubclassOf<UGasExGameplayAbility> Ability = nullptr;

	// the Ability spec register to th AbilitySystemComponent
	FGameplayAbilitySpec AbilitySpec;

};


/**
 * 
 */
UCLASS()
class GASEX_API UGasExAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	

public:

	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY( EditDefaultsOnly , Category = "Gameplay Abilities" , meta=( TitleProperty=Ability ) )
	TArray<FGasExAbilitySetRow>	Abilities;


	// register all the Abilities defined in this Set
	UFUNCTION( BlueprintCallable )
	void Register( UGasExAbilitySystemComponent* ASC );

	// unregister all the Abilities defined in this Set
	UFUNCTION(BlueprintCallable)
	void UnRegister( UGasExAbilitySystemComponent* ASC );

	// Get the Ability Row represented by this given Tag 
	FGasExAbilitySetRow* GetAbilityRow( const FGameplayTag& AbilityTag );

};
