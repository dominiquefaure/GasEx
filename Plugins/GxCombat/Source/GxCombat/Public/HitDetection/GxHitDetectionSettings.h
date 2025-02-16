// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "Math/Color.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GxHitDetectionSettings.generated.h"


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
	float DefaultDebugDrawDuration	=	0.1f;

	/*Debug draw duration when hit something*/
	UPROPERTY( BlueprintReadOnly )
	float HitDebugDrawDuration		=	0.5f;

	/*Color of the Hit Detection shape when not colliding*/
	UPROPERTY( BlueprintReadOnly )
	FColor DefaultDrawColor			=	FColor::Red;

	/*Color of the Hit Detection shape when colliding*/
	UPROPERTY( BlueprintReadOnly )
	FColor HitDrawColor				=	FColor::Green;

	/*thickness to draw the Hit Detection shape*/
	UPROPERTY( BlueprintReadOnly )
	float CollisionShapeThickness	=	1.0f;

	/* Color used to display the Hit markers when it's a Blocking hit*/
	UPROPERTY( BlueprintReadOnly )
	FColor BlockHitMarkerColor		=	FColor::Yellow;

	/* Color used to display the Hit markers when the hit is not blocking*/
	UPROPERTY( BlueprintReadOnly )
	FColor TouchHitMarkerColor		=	FColor::Orange;

	UPROPERTY( BlueprintReadOnly )
	float HitMarkerSize	=	15.0f;

	UPROPERTY( BlueprintReadOnly )
	float HitMarkerLength	=	12.0f;




};

