// Copyright Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StructUtils/InstancedStruct.h"
#include "GxItemTableRow.generated.h"

class UGxItem;

USTRUCT(BlueprintType)
struct GXITEMS_API FGxItemTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:

	// reference to a UGxItem data asset that defines the item
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UGxItem* Item;
};
