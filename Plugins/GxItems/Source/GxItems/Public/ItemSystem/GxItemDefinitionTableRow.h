// Copyright Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StructUtils/InstancedStruct.h"
#include "GxItemDefinition.h"
#include "GxItemDefinitionTableRow.generated.h"

USTRUCT(BlueprintType)
struct GXITEMS_API FGxItemDefinitionTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:

	// structure that defines the item
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TInstancedStruct<FGxItemDefinition> ItemDefinition;
};
