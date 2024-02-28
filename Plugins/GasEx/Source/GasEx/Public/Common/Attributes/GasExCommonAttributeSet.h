// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/AbilitySystem/GasExAttributeSet.h"
#include "GasExCommonAttributeSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GASEX_API UGasExCommonAttributeSet : public UGasExAttributeSet
{
	GENERATED_BODY()
	
public:
	UGasExCommonAttributeSet();


// the Attributes
public:

	UPROPERTY(BlueprintReadOnly , ReplicatedUsing = OnRep_Health , Category = "Attributes|Health" , Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly , ReplicatedUsing = OnRep_MaxHealth , Category = "Attributes|Health" , Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly , ReplicatedUsing = OnRep_Stamina , Category = "Attributes|Health" , Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly , ReplicatedUsing = OnRep_MaxStamina , Category = "Attributes|Health" , Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;



	//---------------------------------------------
	// Attributes Accessors
	//---------------------------------------------

	ATTRIBUTE_ACCESSORS(UGasExCommonAttributeSet , Health);
	ATTRIBUTE_ACCESSORS(UGasExCommonAttributeSet , MaxHealth);

	ATTRIBUTE_ACCESSORS(UGasExCommonAttributeSet , Stamina);
	ATTRIBUTE_ACCESSORS(UGasExCommonAttributeSet , MaxStamina);


	//---------------------------------------------
	// Replication functions
	//---------------------------------------------

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);


protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
