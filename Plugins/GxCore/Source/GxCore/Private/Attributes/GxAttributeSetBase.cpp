// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Attributes/GxAttributeSetBase.h"

//----------------------------------------------------------------------------------------------------------------
void UGxAttributeSetBase::PreAttributeBaseChange( const FGameplayAttribute& Attribute , float& NewValue ) const
{
	Super::PreAttributeBaseChange( Attribute , NewValue );

	ClampAttributeOnChange( Attribute , NewValue );
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
void UGxAttributeSetBase::PreAttributeChange( const FGameplayAttribute& Attribute , float& NewValue )
{
	Super::PreAttributeChange( Attribute , NewValue );

	ClampAttributeOnChange( Attribute , NewValue );
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
void UGxAttributeSetBase::ClampAttributeOnChange( const FGameplayAttribute& Attribute , float& NewValue )const
{

}
//----------------------------------------------------------------------------------------------------------------
