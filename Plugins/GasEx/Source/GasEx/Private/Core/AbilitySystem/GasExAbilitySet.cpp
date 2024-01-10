//All rights reserved Dominique Faure 2023


#include "Core/AbilitySystem/GasExAbilitySet.h"
#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"


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
