// Copyright 2023-2025 Dominique Faure. All Rights Reserved.


#include "AnimNotifies/GxAnimNotifyState_ComboWindow.h"
#include "GameFramework/Character.h"
#include "GxActionComponent.h"

//-----------------------------------------------------------------------------------------
UGxActionComponent* UGxAnimNotifyState_ComboWindow::GetOwnerActionComponent( USkeletalMeshComponent* MeshComponent )
{
	ACharacter* CharacterOwner = Cast<ACharacter>( MeshComponent->GetOwner() );

	if( CharacterOwner != nullptr )
	{
		UActorComponent* Component	=	CharacterOwner->GetComponentByClass( UGxActionComponent::StaticClass() );

		if( Component != nullptr )
		{
			return Cast<UGxActionComponent>( Component );
		}
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxAnimNotifyState_ComboWindow::NotifyBegin( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference )
{
	UGxActionComponent* Component	=	GetOwnerActionComponent( MeshComp );

	if( Component != nullptr )
	{
		Component->OnComboWindowStart( WindowName );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxAnimNotifyState_ComboWindow::NotifyEnd( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference )
{
	UGxActionComponent* Component	=	GetOwnerActionComponent( MeshComp );

	if( Component != nullptr )
	{
		Component->OnComboWindowEnd( WindowName );
	}

}
//-----------------------------------------------------------------------------------------
