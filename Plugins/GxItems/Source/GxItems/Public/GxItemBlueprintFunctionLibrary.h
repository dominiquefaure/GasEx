// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GxItemBlueprintFunctionLibrary.generated.h"

class UDataTable;
class UGxItemInstance;
class UGxItem;

/**
 * 
 */
UCLASS()
class GXITEMS_API UGxItemBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION( BlueprintCallable , Category = "GxItems|ItemDefinition" )
	static UGxItemInstance* CreateInstance( UObject* Outer , UDataTable* DataTable , FName ItemId );

private:

	static UGxItem* GetItemDefinition( UDataTable* DataTable , FName ItemId );
	static UGxItemInstance* CreateInstance( UObject* Outer , UGxItem* Definition );

};
