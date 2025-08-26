// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

#include "GxItemTrait.generated.h"

struct FGxItemInstanceTrait;

/*
* Base class for all iterms Traits
*/
USTRUCT( )
struct GXITEMS_API FGxItemTrait
{
	GENERATED_BODY()

	// The type of the instanced version for this trait
	virtual const UScriptStruct* GetInstanceScriptStruct() const;

};