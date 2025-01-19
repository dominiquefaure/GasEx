// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "Math/Color.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GxHitDetectionSettings.generated.h"

USTRUCT( BlueprintType)
struct FGxHitDetectionKismetDebugDrawSettings
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = KismetTraceSettings , meta = ( Tooltip = "draw Debug duration." ) )
	float DrawDebugTime = 0.2;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = KismetTraceSettings , meta = ( Tooltip = "Color when tracing but not hitting." ) )
	FLinearColor DrawDebugDefaultColor = FLinearColor::Red;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = KismetTraceSettings , meta = ( Tooltip = "Color when hitting." ) )
	FLinearColor DrawDebugHitHitColor = FLinearColor::Green;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = KismetTraceSettings , meta = ( Tooltip = "How you want to debug the trace if at all." ) )
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::Type::ForDuration;
};


UCLASS( config=EditorPerProjectUserSettings , MinimalAPI )
class UGxHitDetectionSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UGxHitDetectionSettings();

	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

public:

	UPROPERTY( BlueprintReadOnly )
	float DefaultDebugDrawDuration		=	0.1f;

	/*Debug draw duration when hit something*/
	UPROPERTY( BlueprintReadOnly )
	float HitDebugDrawDuration			=	0.5f;

	/*Color of the Hit Detection shape when not colliding*/
	UPROPERTY( BlueprintReadOnly )
	FColor CollisionShapeDefaultColor	=	FColor::Red;

	/*Color of the Hit Detection shape when colliding*/
	UPROPERTY( BlueprintReadOnly )
	FColor CollisionShapeHitColor		=	FColor::Green;

	/*thickness to draw the Hit Detection shape*/
	UPROPERTY( BlueprintReadOnly )
	float CollisionShapeThickness		=	1.0f;

	/* Color used to display the Hit markers when it's a Blocking hit*/
	UPROPERTY( BlueprintReadOnly )
	FColor BlockHitMarkerColor			=	FColor::Yellow;

	/* Color used to display the Hit markers when the hit is not blocking*/
	UPROPERTY( BlueprintReadOnly )
	FColor TouchHitMarkerColor			=	FColor::Orange;

	UPROPERTY( BlueprintReadOnly )
	float HitMarkerSize	=	15.0f;

	UPROPERTY( BlueprintReadOnly )
	float HitMarkerLength	=	12.0f;




};

