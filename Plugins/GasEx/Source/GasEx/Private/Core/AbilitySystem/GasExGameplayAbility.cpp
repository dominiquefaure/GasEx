// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/AbilitySystem/GasExGameplayAbility.h"

//-----------------------------------------------------------------------------------------
UGasExGameplayAbility::UGasExGameplayAbility( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
}
//-----------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------
void UGasExGameplayAbility::ActivateAbility( const FGameplayAbilitySpecHandle Handle , const FGameplayAbilityActorInfo* OwnerInfo , const FGameplayAbilityActivationInfo ActivationInfo , const FGameplayEventData* TriggerEventData )
{
	if( TriggerEventData )
	{
		SetParametersFromEvent( TriggerEventData );
	}

	Super::ActivateAbility( Handle , OwnerInfo , ActivationInfo , TriggerEventData );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExGameplayAbility::SetParametersFromEvent( const FGameplayEventData* EventData )
{
	if( ParametersClass )
	{
		if( EventData->OptionalObject != nullptr )
		{
			if( EventData->OptionalObject->IsA( ParametersClass ) )
			{
				Parameters->SetProperties( EventData->OptionalObject );
				//		ParametersClass->StaticClass()->execCast
				//			Parameters=	Cast<ParametersClass->StaticClass()>(EventData->OptionalObject);
			}

		}
	}
}
//-----------------------------------------------------------------------------------------


#if WITH_EDITOR

//-----------------------------------------------------------------------------------------
void UGasExGameplayAbility::PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent )
{
	FString PropertyName	=	PropertyChangedEvent.Property->GetName();
	
	// if the user changed the Parameter class to use
	if( PropertyName == GET_MEMBER_NAME_CHECKED( UGasExGameplayAbility , ParametersClass ) )
	{
		UE_LOG( LogTemp , Warning , TEXT( "Paramter class changed" ) );

		if( Parameters )
		{

		}

		Parameters	=	NewObject< UGasExGameplayAbilityParameters>( this , ParametersClass , NAME_None , RF_Transactional );
	}

	Super::PostEditChangeProperty( PropertyChangedEvent );
}
//-----------------------------------------------------------------------------------------



#endif