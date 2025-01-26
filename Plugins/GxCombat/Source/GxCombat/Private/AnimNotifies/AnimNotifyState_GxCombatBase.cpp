// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "AnimNotifies/AnimNotifyState_GxCombatBase.h"
#include "GameFramework/Character.h"
#include "GxCombatComponent.h"


//-----------------------------------------------------------------------------------------
UGxCombatComponent* UAnimNotifyState_GxCombatBase::GetOwnerCombatComponent( USkeletalMeshComponent* MeshComponent )
{
	ACharacter* CharacterOwner = Cast<ACharacter>( MeshComponent->GetOwner() );

	if( CharacterOwner != nullptr )
	{
		UActorComponent* Component	=	CharacterOwner->GetComponentByClass( UGxCombatComponent::StaticClass() );

		if( Component != nullptr )
		{
			return Cast< UGxCombatComponent>( Component );
		}
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------
