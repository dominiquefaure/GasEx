// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "BaseAttackAbilityParameters.h"

//-----------------------------------------------------------------------------------------
void UBaseAttackAbilityParameters::SetProperties( const UObject* InObject )
{
	const UBaseAttackAbilityParameters* NewValues	=	Cast<UBaseAttackAbilityParameters>( InObject );

	if( NewValues != nullptr )
	{
		AttackMontage	=	NewValues->AttackMontage;
	}
}
//-----------------------------------------------------------------------------------------
