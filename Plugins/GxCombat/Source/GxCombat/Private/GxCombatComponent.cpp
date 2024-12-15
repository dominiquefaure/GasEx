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


UE_DEFINE_GAMEPLAY_TAG( TAG_Event_Combat_Hit , "GxCombat.Event.CollisionHit" )


// Sets default values for this component's properties
UGxCombatComponent::UGxCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bAttackWindowActive=true;
}


// Called when the game starts
void UGxCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UGxCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	for( FGxCombatCollision& Shape : CollisionShapes )
	{
		EvaluateCollisions( Shape );
	}

}

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::AddCollisionShapeComponent( UShapeComponent* Shape , EGxCombatCollisionSlot Slot , EGxCombatCollisionType Type )
{
	FGxCombatCollision NewShape;
	NewShape.CollisionType	=	Type;
	NewShape.CollisionSlot	=	Slot;
	NewShape.ShapeComponent	=	Shape;

	NewShape.SyncComponent	=	Shape;


	Shape->OnComponentBeginOverlap.AddDynamic( this , &UGxCombatComponent::CollisionOverlap );
	//	Shape->SetCollisionEnabled( ECollisionEnabled::NoCollision );
		Shape->SetCollisionEnabled( ECollisionEnabled::QueryOnly );

	CollisionShapes.Add( NewShape );
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
void UGxCombatComponent::CollisionOverlap( UPrimitiveComponent* OverlappedComp , AActor* Other , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	if( bAttackWindowActive )
	{
		// check we don't try to collide with the Owner actor
		if( Other != GetOwner() )
		{
			//	UE_LOG( LogTemp , Error , TEXT( "Collision overlap during attack" ) );

			FGameplayEventData EventData;

	//		FGxCombatHitResult HitResult;
	//		HitResult.OtherActor	=	Other;

	//		EventData.TargetData.Add( new FGxCombatHitResult( HitResult ) );

			EventData.Target		=	Other;

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor( GetOwner<APawn>() , TAG_Event_Combat_Hit , EventData );
		}
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::EvaluateCollisions( FGxCombatCollision& CollisionElement )
{
	FVector Start;
	FVector End;
/*
	if( CollisionShape.SyncComponent != nullptr )
	{
		if( CollisionShape.PreviousTransform.Identical( FTransform::Identity ) )
		{
			Start	=	CollisionShape.PreviousTransform.GetLocation();
		}
		else
		{
			Start	=	End;
		}
	}
	else
	{
		Start	=	CollisionShape.Offset.GetLocation();
		End		=	Start;
	}
*/
	Start	=	CollisionElement.SyncComponent->GetComponentLocation();
	End		=	Start + FVector( 10 , 0 , 0 );



	EvaluateCollisions( Start , End , CollisionElement.Shape );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxCombatComponent::EvaluateCollisions( const FVector& Start , const FVector& End , const FGxCombatCollisionShape& CollisionShape )
{
	FCollisionQueryParams Params;
	TArray<FHitResult> HitResults;


	// Create shape
	FCollisionShape shape;
	if( CollisionShape.ShapeType == EGxCollisionShapeType::BOX )
	{
		shape = FCollisionShape::MakeBox( CollisionShape.BoxHalfExtend );
	}
	else if( CollisionShape.ShapeType == EGxCollisionShapeType::CAPSULE )
	{
		shape = FCollisionShape::MakeCapsule( CollisionShape.CapsuleRadius , CollisionShape.CapsuleHalfHeight );
	}
	else if( CollisionShape.ShapeType == EGxCollisionShapeType::SPHERE )
	{
		shape = FCollisionShape::MakeSphere( CollisionShape.SphereRadius );
	}


	FCollisionQueryParams params;
	params.bTraceComplex = true;
	params.bReturnFaceIndex = true;
	params.bReturnPhysicalMaterial = true;
	params.bIgnoreBlocks = false;
	params.bIgnoreTouches = false;
	params.bSkipNarrowPhase = false;


	UWorld* World	=	GetWorld();
	FQuat Rotation( FVector::ForwardVector , 0.0f );
	World->SweepMultiByChannel( HitResults , Start , End , Rotation , ECC_WorldDynamic , shape , params );


#if !UE_BUILD_SHIPPING
	FGxHitDetectionDebugDraw::DebugDrawBoxSweep( World , Start , End , Rotation , CollisionShape.BoxHalfExtend , HitResults.Num() > 0 );
	FGxHitDetectionDebugDraw::DebugDrawHitResults( World , HitResults );
#endif
}
//-----------------------------------------------------------------------------------------
