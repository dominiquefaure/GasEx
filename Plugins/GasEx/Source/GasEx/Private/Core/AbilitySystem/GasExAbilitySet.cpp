// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/AbilitySystem/GasExAbilitySet.h"
#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"
#include "Core/AbilitySystem/GasExGameplayAbility.h"



//-----------------------------------------------------------------------------------------
void UGasExAbilitySet::Register( UGasExAbilitySystemComponent* ASC )
{
	for( FGasExAbilitySetRow& AbilityRow : Abilities )
	{
		AbilityRow.AbilitySpec = ASC->BuildAbilitySpecFromClass( AbilityRow.Ability , 0 , -1 );
		ASC->GiveAbility( AbilityRow.AbilitySpec );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExAbilitySet::UnRegister( UGasExAbilitySystemComponent* ASC )
{
	for( FGasExAbilitySetRow& AbilityRow : Abilities )
	{
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FGasExAbilitySetRow* UGasExAbilitySet::GetAbilityRow( const FGameplayTag& AbilityTag )
{
	for( FGasExAbilitySetRow& AbilityDef : Abilities )
	{
		if( AbilityDef.AbilityTag == AbilityTag )
		{
			return &AbilityDef;
		}
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------

#if WITH_EDITOR

//-----------------------------------------------------------------------------------------
void UGasExAbilitySet::PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )
{
	FString PropertyName	=	PropertyChangedEvent.Property->GetName();

	// if the user changed the Ability class to use
	if( PropertyName == GET_MEMBER_NAME_CHECKED( FGasExAbilitySetRow , Ability ) )
	{
		SetupRequiredParameterClasses();
	}

	// if the user changed the Custom parameter Flag
	if( PropertyName == GET_MEMBER_NAME_CHECKED( FGasExAbilitySetRow , UseCustomParameters ) )
	{
		SetupRequiredParameterClasses();
	}

	Super::PostEditChangeProperty( PropertyChangedEvent );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExAbilitySet::SetupRequiredParameterClasses()
{
	for( FGasExAbilitySetRow& Row : Abilities )
	{
		if( Row.UseCustomParameters )
		{
			UGasExGameplayAbility* Ability		=	Cast< UGasExGameplayAbility>( Row.Ability->GetDefaultObject() );

			if( Ability )
			{
				if( Ability->ParametersClass != nullptr )
				{
					bool NeedCreateParameters		=	false;
					if( Row.Parameters == nullptr )
					{
						NeedCreateParameters		=	true;
					}
					else
					{
						if( ! Row.Parameters.IsA( Ability->ParametersClass ) )
						{
							NeedCreateParameters	=	true;
						}
					}

					if( NeedCreateParameters )
					{
						Row.Parameters				=	NewObject< UGasExGameplayAbilityParameters>( this , Ability->ParametersClass , NAME_None , RF_Transactional );
					}

				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------

#endif
