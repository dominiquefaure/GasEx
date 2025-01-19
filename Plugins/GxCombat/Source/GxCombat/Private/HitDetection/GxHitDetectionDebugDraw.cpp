// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxHitDetectionDebugDraw.h"
#include "HitDetection/GxHitDetectionSettings.h"

//-----------------------------------------------------------------------------------------
void FGxHitDetectionDebugDraw::DebugDrawBoxSweep( const UWorld* World , const FVector& StartPosition , const FVector& EndPosition , const FQuat& Rotation , const FVector& BoxExtends, bool Hit )
{
#if !UE_BUILD_SHIPPING

	if( true )
	{
		const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();


		FBox StartBox( StartPosition - BoxExtends , StartPosition + BoxExtends );
		FBox EndBox( EndPosition - BoxExtends , EndPosition + BoxExtends );
		FVector direction = Rotation.Vector();

		float LineThickness		=	DebugDrawConfig->CollisionShapeThickness;
		float DebugDrawDuration	=	DebugDrawConfig->DefaultDebugDrawDuration;
		FColor BoxColor			=	DebugDrawConfig->CollisionShapeDefaultColor;
		if( Hit )
		{
			BoxColor			=	DebugDrawConfig->CollisionShapeHitColor;
			DebugDrawDuration	=	DebugDrawConfig->HitDebugDrawDuration;
		}

		DrawDebugBox( World , StartBox.GetCenter() , StartBox.GetExtent() , Rotation , BoxColor , false , DebugDrawDuration , 0 , LineThickness );
		DrawDebugBox( World , EndBox.GetCenter() , EndBox.GetExtent() , Rotation , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// connect the vertices of start box with end box
		FTransform const BoxTransform( Rotation );

		// (-1, -1, 1)
		FVector transform_point = BoxTransform.TransformPosition( FVector( -BoxExtends.X , -BoxExtends.Y , BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// (1, -1, 1)
		transform_point = BoxTransform.TransformPosition( FVector( BoxExtends.X , -BoxExtends.Y , BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// (1, 1, 1)
		transform_point = BoxTransform.TransformPosition( FVector( BoxExtends.X , BoxExtends.Y , BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// (-1, 1, 1)
		transform_point = BoxTransform.TransformPosition( FVector( -BoxExtends.X , BoxExtends.Y , BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		//(-1, -1, -1)
		transform_point = BoxTransform.TransformPosition( FVector( -BoxExtends.X , -BoxExtends.Y , -BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// (1, -1, -1)
		transform_point = BoxTransform.TransformPosition( FVector( BoxExtends.X , -BoxExtends.Y , -BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// (1, 1, -1)
		transform_point = BoxTransform.TransformPosition( FVector( BoxExtends.X , BoxExtends.Y , -BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

		// (-1, 1, -1)
		transform_point = BoxTransform.TransformPosition( FVector( -BoxExtends.X , BoxExtends.Y , -BoxExtends.Z ) );
		DrawDebugLine( World , transform_point + StartPosition , transform_point + EndPosition , BoxColor , false , DebugDrawDuration , 0 , LineThickness );

	}
#endif
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void FGxHitDetectionDebugDraw::DebugDrawHitResults( const UWorld* World , const TArray<FHitResult>& HitResults )
{
#if !UE_BUILD_SHIPPING

	if( true )
	{
		const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

		for( const FHitResult& Hit : HitResults )
		{
			const FColor Color = Hit.bBlockingHit ? DebugDrawConfig->BlockHitMarkerColor : DebugDrawConfig->TouchHitMarkerColor;

			FVector NormalStart = Hit.Location;
			FVector NormalEnd = NormalStart + ( Hit.Normal * DebugDrawConfig->HitMarkerLength );
			DrawDebugDirectionalArrow( World , NormalStart , NormalEnd , DebugDrawConfig->HitMarkerSize , Color , false , DebugDrawConfig->HitDebugDrawDuration );


			FVector ImpactStart = Hit.ImpactPoint;
			FVector ImpactEnd = ImpactStart + ( Hit.ImpactNormal * DebugDrawConfig->HitMarkerLength );
			DrawDebugDirectionalArrow( World , ImpactStart , ImpactEnd , DebugDrawConfig->HitMarkerSize , Color , false , DebugDrawConfig->HitDebugDrawDuration );
		}
	}
#endif
}
//-----------------------------------------------------------------------------------------


