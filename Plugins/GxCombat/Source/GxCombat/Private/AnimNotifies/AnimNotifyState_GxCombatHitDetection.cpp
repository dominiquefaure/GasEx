// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GxCombatComponent.h"
#include "AnimNotifies/AnimNotifyState_GxCombatHitDetection.h"
#include "GameFramework/Character.h"

//-----------------------------------------------------------------------------------------
void UAnimNotifyState_GxCombatHitDetection::NotifyBegin( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference )
{
	UGxCombatComponent* Component	=	GetOwnerCombatComponent( MeshComp );

	if( Component != nullptr )
	{
		Component->StartCollisionDetection( Source , CollisionFilter );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UAnimNotifyState_GxCombatHitDetection::NotifyEnd( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference )
{
	UGxCombatComponent* Component	=	GetOwnerCombatComponent( MeshComp );

	if( Component != nullptr )
	{
		Component->EndCollisionDetection( Source , CollisionFilter );
	}
}
//-----------------------------------------------------------------------------------------
