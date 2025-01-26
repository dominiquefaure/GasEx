// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxCombatComponent.h"
#include "Components/ShapeComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Math/RotationMatrix.h"

#include "HitDetection/GxHitDetectionDebugDraw.h"
#include "GxHitComponent.h"


UE_DEFINE_GAMEPLAY_TAG( TAG_Event_Combat_Hit , "GxCombat.Event.CollisionHit" )


//-----------------------------------------------------------------------------------------
// Sets default values for this component's properties
UGxCombatComponent::UGxCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bAttackWindowActive=true;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called when the game starts
void UGxCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called every frame
void UGxCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::RegisterHitComponent( EGxCollisionSource InSource , UGxHitComponent* InComponent )
{
	FGxInitiatorCollisionComponent NewComponent;
	NewComponent.CollisionSource	=	InSource;
	NewComponent.HitComponent		=	InComponent;
	HitComponents.Add( NewComponent );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::UnRegisterHitComponent( EGxCollisionSource InSource )
{

}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
void UGxCombatComponent::StartCollisionDetection( EGxCollisionSource InSource , const FString& InHitComponentFilter )
{
	for( FGxInitiatorCollisionComponent& Element : HitComponents )
	{
		if( Element.CollisionSource == InSource )
		{
			Element.HitComponent->SetHitDetectionEnable( true );
		}
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::EndCollisionDetection( EGxCollisionSource InSource , const FString& InHitComponentFilter )
{
	for( FGxInitiatorCollisionComponent& Element : HitComponents )
	{
		if( Element.CollisionSource == InSource )
		{
			Element.HitComponent->SetHitDetectionEnable( false );
		}
	}

}
//-----------------------------------------------------------------------------------------
