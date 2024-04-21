// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Core/AnimNotifies/GasExAnimNotifyState_CancelAction.h"
#include "GameFramework/Character.h"
#include "Components/GasExActionSystemComponent.h"


//-----------------------------------------------------------------------------------------
UGasExActionSystemComponent* UGasExAnimNotifyState_CancelAction::GetOwnerActionComponent( USkeletalMeshComponent* MeshComponent )
{
	ACharacter* CharacterOwner = Cast<ACharacter>( MeshComponent->GetOwner() );

	if( CharacterOwner != nullptr )
	{
		UActorComponent* Component	=	CharacterOwner->GetComponentByClass( UGasExActionSystemComponent::StaticClass() );

		if( Component != nullptr )
		{
			return Cast< UGasExActionSystemComponent>( Component );
		}
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExAnimNotifyState_CancelAction::NotifyBegin( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference )
{
	UGasExActionSystemComponent* Component	=	GetOwnerActionComponent( MeshComp );

	if( Component != nullptr )
	{
		Component->OnCancelWindowStart( WindowName );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExAnimNotifyState_CancelAction::NotifyEnd( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference )
{
	UGasExActionSystemComponent* Component	=	GetOwnerActionComponent( MeshComp );

	if( Component != nullptr )
	{
		Component->OnCancelWindowEnd( WindowName );
	}

}
//-----------------------------------------------------------------------------------------
