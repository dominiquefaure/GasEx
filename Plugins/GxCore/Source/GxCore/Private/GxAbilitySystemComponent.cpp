// Copyright 2023-2025 Dominique Faure. All Rights Reserved.


#include "GxAbilitySystemComponent.h"

//-----------------------------------------------------------------------------------------
void UGxAbilitySystemComponent::RegisterAbilitySet( UGxAbilitySet* AbilitySet , FGxAbilitySetHandle& OutHandle )
{
	if (!AbilitySet)
	{
		OutHandle = FGxAbilitySetHandle();
		return;
	}

	FGxAbilitySetHandle* ExistingHandle = GetAbilitySetHandle(AbilitySet);
	if (ExistingHandle)
	{
		OutHandle = *ExistingHandle;
		return;
	}

	FGxAbilitySetHandle NewHandle;
	NewHandle.AbilitySet = AbilitySet;

	// Grant Abilities
	for (const FGxAbilitySet_GameplayAbility& AbilityDef : AbilitySet->GameplayAbilities)
	{
		if (AbilityDef.Ability)
		{
			FGameplayAbilitySpec Spec(AbilityDef.Ability, AbilityDef.AbilityLevel, INDEX_NONE, this);
			FGameplayAbilitySpecHandle SpecHandle = GiveAbility(Spec);
			NewHandle.AbilitySpecHandles.Add(SpecHandle);
		}
	}

	// Grant Effects
	for (const FGxAbilitySet_GameplayEffect& EffectDef : AbilitySet->GameplayEffects)
	{
		if (EffectDef.GameplayEffect)
		{
			FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectToSelf(EffectDef.GameplayEffect->GetDefaultObject<UGameplayEffect>(), EffectDef.EffectLevel, FGameplayEffectContextHandle());
			NewHandle.GameplayEffectHandles.Add(EffectHandle);
		}
	}

/*
	// Grant Attribute Sets
	for (const FGxAbilitySet_AttributeSet& AttrDef : AbilitySet->Attributes)
	{
		if (AttrDef.AttributeSet)
		{
			UAttributeSet* NewSet = NewObject<UAttributeSet>(this, AttrDef.AttributeSet);
			GrantedAttributeSets.Add(NewSet);
			NewHandle.GrantedAttributeSets.Add(NewSet);
		}
	}
*/
	RegisteredAbilitySets.Add(NewHandle);
	OutHandle = NewHandle;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxAbilitySystemComponent::UnRegisterAbilitySet( UGxAbilitySet* AbilitySet )
{
	FGxAbilitySetHandle* Handle = GetAbilitySetHandle( AbilitySet );

	if( Handle != nullptr )
	{
		UnRegisterAbilitySetFromHandle( *Handle );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxAbilitySystemComponent::UnRegisterAbilitySetFromHandle( FGxAbilitySetHandle& Handle )
{
	RegisteredAbilitySets.Remove( Handle );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
FGxAbilitySetHandle* UGxAbilitySystemComponent::GetAbilitySetHandle( UGxAbilitySet* AbilitySet )
{
	for( FGxAbilitySetHandle& Handle : RegisteredAbilitySets )
	{
		if ( Handle.AbilitySet == AbilitySet )
		{
			return &Handle;
		}
	}
	return nullptr;
}
//-----------------------------------------------------------------------------------------
