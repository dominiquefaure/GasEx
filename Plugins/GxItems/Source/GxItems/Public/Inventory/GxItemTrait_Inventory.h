// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "ItemSystem/GxItemTrait.h"
#include "GxItemTrait_Inventory.generated.h"

/*
* Base class for all iterms Traits
*/
USTRUCT( BlueprintType )
struct GXITEMS_API FGxItemTrait_Inventory : public FGxItemTrait
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly )
	FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnlY )
	FString ItemDescription;


	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Inventory" )
	int MaxCountInInventory = 1;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Inventory" )
	UTexture2D* Icon;

};