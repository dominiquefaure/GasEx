// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GxAttributeSetBase.generated.h"


/**
 * This macro defines a set of helper functions for accessing and initializing attributes.
 *
 * The following example of the macro:
 *		ATTRIBUTE_ACCESSORS(ULyraHealthSet, Health)
 * will create the following functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GXCORE_API UGxAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
	virtual void PreAttributeBaseChange( const FGameplayAttribute& Attribute , float& NewValue ) const override;
	virtual void PreAttributeChange( const FGameplayAttribute& Attribute , float& NewValue ) override;

	virtual void ClampAttributeOnChange( const FGameplayAttribute& Attribute , float& NewValue )const;

};
