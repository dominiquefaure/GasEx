// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "HitDetection/GxHitDetectionQuery.h"

//-----------------------------------------------------------------------------------------
void UGxHitDetectionQuery::PerformHitDetection( TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	if( OwnerActor == nullptr )
	{
		return;
	}

	FVector ActorLocation	=	OwnerActor->GetActorLocation();

	if( Anchor.AnchorType == EGxHitAnchorType::Absolute )
	{
		PerformAbsoluteHitDetection( ActorLocation , OutHits , InDebugDrawSettings );
	}
	else
	{
		PerformSocketsHitDetection( ActorLocation , OutHits , InDebugDrawSettings );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformAbsoluteHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	FVector Location	=	InActorLocation + Anchor.Position;

	return PerformHitDetection( Location , OutHits , InDebugDrawSettings );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformSocketsHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	bool Result	=	false;
	FVector Location	=	InActorLocation;

	// temp, generate the sockets the 1st time
	if( Sockets.Num() == 0 )
	{
		GenerateSocketInstances();
	}


	for( FGxHitDetectionQueryInstance& SocketInstance : Sockets )
	{
		TArray<FHitResult> HitResults;

		if( SocketInstance.Component != nullptr )
		{
			Location	=	SocketInstance.Component->GetSocketLocation( SocketInstance.SocketName );

			if( PerformHitDetection( Location , OutHits , InDebugDrawSettings ) )
			{
				Result	=	true;
			}
		}
	}

	return Result;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxHitDetectionQuery::GenerateSocketInstances()
{
	if( OwnerActor == nullptr )
	{
		return;
	}

	// search for all the sockets in all the PrimitiveComponents of the owning actor
	FString StartSocketName=	Anchor.Socket.ToString();
	for( UActorComponent* ActorComponent : OwnerActor->GetComponents() )
	{
		UPrimitiveComponent* PrimitiveComponent	=	Cast< UPrimitiveComponent>( ActorComponent );

		if( PrimitiveComponent != nullptr )
		{
			for( FName& Name : PrimitiveComponent->GetAllSocketNames() )
			{
				if( Name.ToString().StartsWith( StartSocketName ) )
				{
					FGxHitDetectionQueryInstance SocketInstance;
					SocketInstance.Component	=	PrimitiveComponent;
					SocketInstance.SocketName	=	Name;
					SocketInstance.Offset		=	FVector( 0 , 0 , 0 );

					Sockets.Add( SocketInstance );
				}
			}
		}
	}

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformHitDetection( const FVector& InLocation , TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	if( AllowMultiTrace )
	{
		TArray<FHitResult> HitResults;
		if( PerformHitDetectionMulti( InLocation , HitResults , InDebugDrawSettings ) )
		{
			for( FHitResult& HitResult : HitResults )
			{
				OutHits.Add( HitResult );
			}
			return true;
		}
	}
	else
	{
		FHitResult HitResult;
		if( PerformHitDetectionSingle( InLocation , HitResult , InDebugDrawSettings ) )
		{
			OutHits.Add( HitResult );
			return true;
		}

	}

	return false;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformHitDetectionSingle( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	switch( QueryMethod.QueryType )
	{
		case EGxHitDetectionQueryType::Channel:
			return PerformTraceSingleByChannel( InLocation , OutResult , InDebugDrawSettings );
		break;
		case EGxHitDetectionQueryType::Profile:
			return PerformTraceSingleByProfile( InLocation , OutResult , InDebugDrawSettings );
		break;
		case EGxHitDetectionQueryType::Object:
			return PerformTraceSingleForObjects( InLocation , OutResult , InDebugDrawSettings );
		break;
	}
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformHitDetectionMulti( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	switch( QueryMethod.QueryType )
	{
		case EGxHitDetectionQueryType::Channel:
			return	PerformTraceMultiByChannel( InLocation , OutResult , InDebugDrawSettings );
		break;
		case EGxHitDetectionQueryType::Profile:
			return	PerformTraceMultiByProfile( InLocation , OutResult , InDebugDrawSettings );
		break;
		case EGxHitDetectionQueryType::Object:
			return PerformTraceMultiForObjects( InLocation , OutResult , InDebugDrawSettings );
		break;
	}
	return false;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceSingleByChannel( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceSingle( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceSingle( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::CAPSULE:
		return UKismetSystemLibrary::CapsuleTraceSingle( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime);
	}

	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceSingleByProfile( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceSingleByProfile( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceSingleByProfile( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceSingleByProfile( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
	}
	
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceSingleForObjects( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{
	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceSingleForObjects( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceSingleForObjects( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceSingleForObjects( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
	}

	return false;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceMultiByChannel( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{

	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceMulti( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceMulti( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceMulti( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
	}

	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceMultiByProfile( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{

	FRotator Orientation	=	FRotator( 0 , 0 , 0 );
	
	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceMultiByProfile( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceMultiByProfile( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceMultiByProfile( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
	}
	
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceMultiForObjects( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )
{

	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceMultiForObjects( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceMultiForObjects( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceMultiForObjects( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , InDebugDrawSettings.DrawDebugType , OutResult , bIgnoreSelf , InDebugDrawSettings.DrawDebugDefaultColor , InDebugDrawSettings.DrawDebugHitHitColor , InDebugDrawSettings.DrawDebugTime );
	}

	return false;
}
//-----------------------------------------------------------------------------------------
