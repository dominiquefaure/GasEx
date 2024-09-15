// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"

#include "GasExAbilitySystemComponent.generated.h"

class UGasExAbilitySet;
class UGasExGraph;


/**
 * 
 */
UCLASS( ClassGroup=( GasEx ) , meta=( BlueprintSpawnableComponent ) )
class GASEX_API UGasExAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	UGasExAbilitySystemComponent( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Ability Sets" )
	TObjectPtr<UGasExAbilitySet> DefaultAbilitySet;

	// Try Activate an Ability registered from an AbilitySet
	UFUNCTION( BlueprintCallable)
	bool TryActivateExAbility( const FGameplayTag& AbilityTag);

	UFUNCTION( BlueprintCallable )
	void CancelExAbility( const FGameplayTag& AbilityTag );

	const FGameplayTag& GetExAbilityTagFromHandle( const FGameplayAbilitySpecHandle& Handle );


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void NotifyAbilityEnded( FGameplayAbilitySpecHandle Handle , UGameplayAbility* Ability , bool bWasCancelled ) override;

private:

	// Get the Ability Row represented by this given Tag 
	FGasExAbilitySetRow* GetAbilityDef( const FGameplayTag& AbilityTag );

	// Get the Ability Row represented by this given Handle 
	FGasExAbilitySetRow* GetAbilityDef(const FGameplayAbilitySpecHandle& Handle );

	virtual void NotifyAbilityFailed( const FGameplayAbilitySpecHandle Handle , UGameplayAbility* Ability , const FGameplayTagContainer& FailureReason )override;

private:

	// others AbilitySet added at runtime
	TArray<UGasExAbilitySet*> AdditionalAbilitySets;

};
