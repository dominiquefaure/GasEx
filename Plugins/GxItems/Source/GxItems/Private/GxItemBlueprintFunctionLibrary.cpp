	// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#include "GxItemBlueprintFunctionLibrary.h"
#include "StructUtils/InstancedStruct.h"

#include "ItemSystem/GxItem.h"
#include "ItemSystem/GxItemInstance.h"
#include "ItemSystem/GxItemTableRow.h"

//----------------------------------------------------------------------------------------------------------------
UGxItem* UGxItemBlueprintFunctionLibrary::GetItemDefinition( UDataTable* DataTable , FName ItemId )
{
	if( DataTable )
	{
		static const FString ContextString(TEXT("GxItemBlueprintFunctionLibrary::GetItemDefinition"));
		if( const FGxItemTableRow* Row = DataTable->FindRow<FGxItemTableRow>( ItemId , ContextString ) )
		{
			return Row->Item;
		}
	}
	return nullptr;
}
//----------------------------------------------------------------------------------------------------------------


UGxItemInstance* UGxItemBlueprintFunctionLibrary::CreateInstance( UObject* Outer , UGxItem* Definition )
{
	if( !Definition  )
	{
		return nullptr;
	}
	// Create a new instance of the item definition
	return Definition->CreateInstance( Outer );
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
UGxItemInstance* UGxItemBlueprintFunctionLibrary::CreateInstance( UObject* Outer , UDataTable* DataTable , FName ItemId )
{
	UGxItem* Definition = GetItemDefinition( DataTable , ItemId );

	if( Definition != nullptr )
	{
		return CreateInstance( Outer , Definition );
	}

	return nullptr;
}
//----------------------------------------------------------------------------------------------------------------
