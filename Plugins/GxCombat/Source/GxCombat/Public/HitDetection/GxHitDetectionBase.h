// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HitDetection/GxHitDetectionSettings.h"
#include "GxHitDetectionBase.generated.h"

/**
 * 
 */
UCLASS( )
class GXCOMBAT_API UGxHitDetectionBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Transient )
	AActor* OwnerActor;

	virtual void Setup( AActor* InOwner );
	virtual void PerformHitDetection( TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings){}

protected:

	UPROPERTY(Transient)
	TArray<AActor*> IgnoredActors;



};
