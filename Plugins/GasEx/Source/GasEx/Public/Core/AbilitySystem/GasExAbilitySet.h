// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"

#include "GasExAbilitySet.generated.h"


class UGasExAbilitySystemComponent;
class UGasExGameplayAbility;
class UGasExGameplayAbilityParameters;


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
	// Gameplay ability to grant.
	//UPROPERTY( EditAnywhere , BlueprintReadOnly )
	//	TSubObjectPtr<UGasExGameplayAbility> Ability2 = nullptr;

	// the Ability spec register to th AbilitySystemComponent
	FGameplayAbilitySpec AbilitySpec;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category=Parameters )
	bool UseCustomParameters;

	UPROPERTY( Export , Instanced , EditAnywhere , BlueprintReadOnly , Category=Parameters , meta=( ShowOnlyInnerProperties ) )
	TObjectPtr< UGasExGameplayAbilityParameters> Parameters;


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

#if WITH_EDITOR
	void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )override;
#endif

private:

	void SetupRequiredParameterClasses();

};
