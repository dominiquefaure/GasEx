// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "Math/Color.h"


struct GXCOMBAT_API FGxHitDetectionDebugDraw
{
	static void DebugDrawBoxSweep( const UWorld* World , const FVector& StartPosition , const FVector& EndPosition , const FQuat& Rotation , const FVector& BoxExtends , bool Hit );

	static void DebugDrawHitResults( const UWorld* World , const TArray<FHitResult>& HitResults );

};

