// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once
#include "GxHitDetectionStructs.generated.h"


UENUM( BlueprintType )
enum class EGxHitShapeType: uint8
{
	BOX = 0 UMETA( DisplayName = "Box" ) ,
	CAPSULE UMETA( DisplayName = "Capsule" ) ,
	SPHERE UMETA( DisplayName = "Sphere" )
};

USTRUCT( BlueprintType  )
struct FGxHitDetectionShape
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Type of Shape to use for Collision" ) )
	EGxHitShapeType ShapeType;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Box Half Extent" , EditCondition = "ShapeType == EGxHitShapeType::BOX" , EditConditionHides ) )
	FVector BoxHalfExtend	=	FVector( 50 , 50 , 50 );

	// Capsule shape values
	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Capsule Half Height" , EditCondition = "ShapeType == EGxHitShapeType::CAPSULE" , EditConditionHides ) )
	float CapsuleHalfHeight	=	50;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Capsule Radius" , EditCondition = "ShapeType == EGxHitShapeType::CAPSULE" , EditConditionHides ) )
	float CapsuleRadius	=	10;

	// Sphere values
	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Sphere Radius" , EditCondition = "ShapeType == EGxHitShapeType::SPHERE" , EditConditionHides ) )
	float SphereRadius	=	10;
};


UENUM( BlueprintType )
enum class EGxHitAnchorType : uint8
{
	Absolute = 0 ,
	Sockets
};

USTRUCT( BlueprintType )
struct FGxHitDetectionAnchor
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EGxHitAnchorType AnchorType;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Delta position from the Owner Actor location" , EditCondition = "AnchorType == EGxHitAnchorType::Absolute" , EditConditionHides ) )
	FVector Position;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Name of the socket to use, if there is more than 1 with that starting name, will generate a shape per socket" , EditCondition = "AnchorType == EGxHitAnchorType::Sockets" , EditConditionHides ) )
	FName Socket;
};

USTRUCT( )
struct FGxHitDetectionSocketInstance
{
	GENERATED_BODY()

	UPROPERTY()
	FName Socket;

	// position of the Socket relative to the Actor
	UPROPERTY()
	FVector Position;
};