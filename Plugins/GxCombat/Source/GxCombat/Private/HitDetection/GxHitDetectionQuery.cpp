// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "HitDetection/GxHitDetectionQuery.h"

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformHitDetection( TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	if( OwnerActor == nullptr )
	{
		return false;
	}

	FVector ActorLocation	=	OwnerActor->GetActorLocation();

	if( Anchor.AnchorType == EGxHitAnchorType::Absolute )
	{
		return PerformAbsoluteHitDetection( ActorLocation , OutHits , IgnoredActors );
	}
	else
	{
		return PerformSocketsHitDetection( ActorLocation , OutHits , IgnoredActors );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformAbsoluteHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	FVector Location	=	InActorLocation + Anchor.Position;

	return PerformHitDetection( Location , OutHits  , IgnoredActors );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformSocketsHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors )
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

			if( PerformHitDetection( Location , OutHits , IgnoredActors ) )
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
bool UGxHitDetectionQuery::PerformHitDetection( const FVector& InLocation , TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	if( AllowMultiTrace )
	{
		TArray<FHitResult> HitResults;
		if( PerformHitDetectionMulti( InLocation , HitResults , IgnoredActors ) )
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
		if( PerformHitDetectionSingle( InLocation , HitResult , IgnoredActors ) )
		{
			OutHits.Add( HitResult );
			return true;
		}

	}

	return false;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformHitDetectionSingle( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	switch( QueryMethod.QueryType )
	{
		case EGxHitDetectionQueryType::Channel:
			return PerformTraceSingleByChannel( InLocation , OutResult , IgnoredActors );
		break;
		case EGxHitDetectionQueryType::Profile:
			return PerformTraceSingleByProfile( InLocation , OutResult , IgnoredActors );
		break;
		case EGxHitDetectionQueryType::Object:
			return PerformTraceSingleForObjects( InLocation , OutResult , IgnoredActors );
		break;
	}
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformHitDetectionMulti( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	switch( QueryMethod.QueryType )
	{
		case EGxHitDetectionQueryType::Channel:
			return	PerformTraceMultiByChannel( InLocation , OutResult , IgnoredActors );
		break;
		case EGxHitDetectionQueryType::Profile:
			return	PerformTraceMultiByProfile( InLocation , OutResult , IgnoredActors );
		break;
		case EGxHitDetectionQueryType::Object:
			return PerformTraceMultiForObjects( InLocation , OutResult , IgnoredActors );
		break;
	}
	return false;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceSingleByChannel( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceSingle( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceSingle( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::CAPSULE:
		return UKismetSystemLibrary::CapsuleTraceSingle( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
	}

	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceSingleByProfile( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	FRotator Orientation	=	FRotator( 0 , 0 , 0 );

	const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceSingleByProfile( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceSingleByProfile( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor  , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceSingleByProfile( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
	}
	
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceSingleForObjects( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{
	FRotator Orientation	=	FRotator( 0 , 0 , 0 );
	const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceSingleForObjects( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceSingleForObjects( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceSingleForObjects( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
	}

	return false;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceMultiByChannel( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{

	FRotator Orientation	=	FRotator( 0 , 0 , 0 );
	const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceMulti( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceMulti( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceMulti( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.TraceChannel , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
	}

	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceMultiByProfile( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{

	FRotator Orientation	=	FRotator( 0 , 0 , 0 );
	const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceMultiByProfile( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceMultiByProfile( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceMultiByProfile( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ProfileName , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
	}
	
	return false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool UGxHitDetectionQuery::PerformTraceMultiForObjects( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors )
{

	FRotator Orientation	=	FRotator( 0 , 0 , 0 );
	const UGxHitDetectionSettings* DebugDrawConfig	=	GetDefault<UGxHitDetectionSettings>();

	switch( Shape.ShapeType )
	{
		case EGxHitShapeType::BOX:
			return UKismetSystemLibrary::BoxTraceMultiForObjects( OwnerActor , InLocation , InLocation , Shape.BoxHalfExtend , Orientation , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::SPHERE:
			return UKismetSystemLibrary::SphereTraceMultiForObjects( OwnerActor , InLocation , InLocation , Shape.SphereRadius , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
		case EGxHitShapeType::CAPSULE:
			return UKismetSystemLibrary::CapsuleTraceMultiForObjects( OwnerActor , InLocation , InLocation , Shape.CapsuleRadius , Shape.CapsuleHalfHeight , QueryMethod.ObjectTypes , UseComplexTrace , IgnoredActors , EDrawDebugTrace::Type::ForDuration , OutResult , bIgnoreSelf , DebugDrawConfig->DefaultDrawColor , DebugDrawConfig->HitDrawColor , DebugDrawConfig->DefaultDebugDrawDuration );
	}

	return false;
}
//-----------------------------------------------------------------------------------------
