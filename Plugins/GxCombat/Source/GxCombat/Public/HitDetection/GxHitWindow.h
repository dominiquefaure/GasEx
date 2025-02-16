// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HitDetection/GxHitDetectionBase.h"
#include "GxHitWindow.generated.h"

/**
 * 
 */
USTRUCT( )
struct GXCOMBAT_API FGxHitWindow
{
	GENERATED_BODY()
	
public:

	UPROPERTY( Transient )
	EGxCollisionSource Source;

	UPROPERTY( Transient )
	FString CollisionFilter;

	UPROPERTY( Transient )
	bool AllowMultiHit;

	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> IgnoredActors;

	UPROPERTY( Transient )
	TArray<UGxHitDetectionBase*> HitElements;

	bool PerformHitDetection( TArray<FHitResult>& OutHits );

};
