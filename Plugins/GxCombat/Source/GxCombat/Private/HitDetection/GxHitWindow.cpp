// Copyright 2023-2025 Dominique Faure. All Rights Reserved.


#include "HitDetection/GxHitWindow.h"

//-----------------------------------------------------------------------------------------
bool FGxHitWindow::PerformHitDetection( TArray<FHitResult>& OutHits )
{
	bool Result	=	false;

	TArray<FHitResult> Results;

	for( UGxHitDetectionBase* Element : HitElements )
	{
		if( Element->PerformHitDetection( OutHits , IgnoredActors ) )
		{
			Result=	true;
		}
	}

	return Result;
}
//-----------------------------------------------------------------------------------------
