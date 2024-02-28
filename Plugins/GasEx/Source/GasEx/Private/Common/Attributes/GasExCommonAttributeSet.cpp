// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Common/Attributes/GasExCommonAttributeSet.h"
#include "Net/UnrealNetwork.h"

//-----------------------------------------------------------------------------------------
UGasExCommonAttributeSet::UGasExCommonAttributeSet()
	: Health(100.0f)
	, MaxHealth(100.0f)
	, Stamina(100.0f)
	, MaxStamina( 100.0f)
{
}
//-----------------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------------
void UGasExCommonAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGasExCommonAttributeSet , Health , COND_None , REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasExCommonAttributeSet , MaxHealth , COND_None , REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasExCommonAttributeSet , Stamina , COND_None , REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGasExCommonAttributeSet , MaxStamina , COND_None , REPNOTIFY_Always);

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasExCommonAttributeSet , Health , OldValue);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasExCommonAttributeSet , MaxHealth , OldValue);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasExCommonAttributeSet , Stamina , OldValue);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGasExCommonAttributeSet , MaxStamina , OldValue);
}
//-----------------------------------------------------------------------------------------
