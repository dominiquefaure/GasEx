//All rights reserved Dominique Faure 2023


#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"
#include "GasExAbilitySystemComponent.generated.h"

class UGasExAbilitySet;

/**
 * 
 */
UCLASS()
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// Get the Ability Row represented by this given Tag 
	FGasExAbilitySetRow* GetAbilityDef( const FGameplayTag& AbilityTag );


private:

	// others AbilitySet added at runtime
	TArray<UGasExAbilitySet*> AdditionalAbilitySets;
};
