// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Attributes/GxHealthAttributeSet.h"
#include "Net/UnrealNetwork.h"


//----------------------------------------------------------------------------------------------------------------
void UGxHealthAttributeSet::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME_CONDITION_NOTIFY( UGxHealthAttributeSet , Health , COND_None , REPNOTIFY_Always );
	DOREPLIFETIME_CONDITION_NOTIFY( UGxHealthAttributeSet , MaxHealth , COND_None , REPNOTIFY_Always );
}
//----------------------------------------------------------------------------------------------------------------


//////////
// Replications
//////////

//----------------------------------------------------------------------------------------------------------------
void UGxHealthAttributeSet::OnRep_Health( const FGameplayAttributeData& OldHealth ) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UGxHealthAttributeSet , Health , OldHealth );
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
void UGxHealthAttributeSet::OnRep_MaxHealth( const FGameplayAttributeData& OldMaxHealth ) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UGxHealthAttributeSet , MaxHealth , OldMaxHealth );
}
//----------------------------------------------------------------------------------------------------------------
