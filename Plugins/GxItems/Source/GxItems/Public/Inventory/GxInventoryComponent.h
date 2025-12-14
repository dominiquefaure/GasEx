// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "ItemSystem/GxItemTrait.h"
#include "GxInventoryComponent.generated.h"

UCLASS( ClassGroup = (Gx) , meta = (BlueprintSpawnableComponent) )
class GXITEMS_API UGxInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGxInventoryComponent( );
};