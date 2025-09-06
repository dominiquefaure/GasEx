// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GxAbilitySystemComponent.generated.h"

class UGxAbilitySet; 
struct FGxAbilitySetHandle;

/**
 * 
 */
UCLASS( ClassGroup=( Gx ) , meta=( BlueprintSpawnableComponent ) )
class GXCORE_API UGxAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
// Properties
private:
	UPROPERTY()
	TArray<FGxAbilitySetHandle> RegisteredAbilitySets;



public:

	UFUNCTION(BlueprintCallable)
	void RegisterAbilitySet( UGxAbilitySet* AbilitySet , FGxAbilitySetHandle& OutHandle );

	UFUNCTION(BlueprintCallable)
	void UnRegisterAbilitySet( UGxAbilitySet* AbilitySet );

	UFUNCTION(BlueprintCallable)
	void UnRegisterAbilitySetFromHandle( FGxAbilitySetHandle& Handle );


private:

	// Get the handle for a registered ability set
	FGxAbilitySetHandle* GetAbilitySetHandle( UGxAbilitySet* AbilitySet );

};
