// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "GasExGameplayAbility.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam( FGasExAbilityEnded , bool Canceled );

class UGasExGameplayAbilityParameters;

/**
 * 
 */
UCLASS()
class GASEX_API UGasExGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGasExGameplayAbility( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );


	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category=Parameters , meta=( DisplayName="Parameters Class" ) )
	TSubclassOf<class UGasExGameplayAbilityParameters> ParametersClass;

	UPROPERTY( Export , Instanced , EditAnywhere , BlueprintReadOnly , Category=Parameters , meta=( ShowOnlyInnerProperties ) )
	TObjectPtr< UGasExGameplayAbilityParameters> Parameters;


	void SetParametersFromEvent( const FGameplayEventData*  EventData );


	virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle , const FGameplayAbilityActorInfo* OwnerInfo , const FGameplayAbilityActivationInfo ActivationInfo , const FGameplayEventData* TriggerEventData ) override;


#if WITH_EDITOR
	void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )override;
#endif


};
