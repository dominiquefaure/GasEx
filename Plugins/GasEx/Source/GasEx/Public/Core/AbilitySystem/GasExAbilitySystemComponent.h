// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"

#include "Core/AbilityGraph/GasExGraphInstance.h"


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

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Ability Sets" )
	TObjectPtr<UGasExGraph> DefaultAbilityGraph;

	// Try Activate an Ability registered from an AbilitySet
	UFUNCTION( BlueprintCallable)
	bool TryActivateExAbility( const FGameplayTag& AbilityTag);

	// temp function
	UFUNCTION( BlueprintCallable )
	void TryActivateNextGraphNode();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// Get the Ability Row represented by this given Tag 
	FGasExAbilitySetRow* GetAbilityDef( const FGameplayTag& AbilityTag );


private:

	// others AbilitySet added at runtime
	TArray<UGasExAbilitySet*> AdditionalAbilitySets;


	TObjectPtr<UGasExGraphInstance> GraphInstance;
};
