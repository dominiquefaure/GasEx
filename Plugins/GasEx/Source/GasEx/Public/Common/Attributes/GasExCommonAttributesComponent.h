// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"

#include "GasExCommonAttributesComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGasExAttributeChanged , UGasExCommonAttributesComponent* , AttributeComponent , float , OldValue , float , NewValue , AActor* , Instigator);


class UGasExAbilitySystemComponent;
class UGasExCommonAttributeSet;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASEX_API UGasExCommonAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGasExCommonAttributesComponent();


	// Returns the current health value.
	UFUNCTION(BlueprintCallable , Category = "Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable , Category = "Health")
	float GetMaxHealth() const;

	// Returns the current Stamina value.
	UFUNCTION(BlueprintCallable , Category = "Stamina")
	float GetStamina() const;

	// Returns the current maximum Stamina value.
	UFUNCTION(BlueprintCallable , Category = "Stamina")
	float GetMaxStamina() const;




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data);
	virtual void OnStaminaAttributeChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxStaminaAttributeChanged(const FOnAttributeChangeData& Data);


	//////////////
	// Delegates
	///////////////

	UPROPERTY(BlueprintAssignable)
	FGasExAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FGasExAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FGasExAttributeChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FGasExAttributeChanged OnMaxStaminaChanged;


private:

	void LinkToAbilitySystem(UGasExAbilitySystemComponent* ASC);
	void UnlinkFromAbilitySystem();

	// Ability system used by this component.
	UPROPERTY()
	TObjectPtr<UGasExAbilitySystemComponent> AbilitySystemComponent;


	// the attribute set used by this component.
	UPROPERTY()
	TObjectPtr<const UGasExCommonAttributeSet> CommonAttributeSet;

};
