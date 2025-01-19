// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GxHealthAttributeSet.generated.h"



/**
 * 
 */
UCLASS()
class GXCORE_API UGxHealthAttributeSet : public UGxAttributeSetBase
{
	GENERATED_BODY()

// Attributes
public:

	UPROPERTY( BlueprintReadOnly , ReplicatedUsing = OnRep_Health , Category = "Attributes | Health" , Meta =( AllowPrivateAccesss = true ) )
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS( UGxHealthAttributeSet , Health );

	UPROPERTY( BlueprintReadOnly , ReplicatedUsing = OnRep_MaxHealth , Category = "Attributes | Health" , Meta = ( AllowPrivateAccesss = true ) )
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS( UGxHealthAttributeSet , MaxHealth );


// Overrides
public:

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps )const override;


// Replicated functions
protected:

	UFUNCTION()
	virtual void OnRep_Health( const FGameplayAttributeData& OldHealth )const;

	UFUNCTION()
	virtual void OnRep_MaxHealth( const FGameplayAttributeData& OldHealth )const;


};
