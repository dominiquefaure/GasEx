// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxItemBlueprintFunctionLibrary.h"

#include "ItemSystem/GxItemDefinition.h"
#include "ItemSystem/GxItemInstance.h"

#include "StructUtils/InstancedStruct.h"


//----------------------------------------------------------------------------------------------------------------
const FGxItemDefinition* UGxItemBlueprintFunctionLibrary::GetItemDefinition( UDataTable* DataTable , FName ItemId )
{
	if( DataTable )
	{
		// Find the row in the data table with the specified ItemId
		static const FString ContextString(TEXT("GxItemBlueprintFunctionLibrary::GetItemDefinition"));
		if( const FGxItemDefinitionTableRow* Row = DataTable->FindRow<FGxItemDefinitionTableRow>( ItemId , ContextString ) )
		{
			return Row->ItemDefinition.GetPtr<FGxItemDefinition>();
		}
	}
	return nullptr;
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
UGxItemInstance* UGxItemBlueprintFunctionLibrary::CreateInstance( UObject* Outer , const FGxItemDefinition* Definition )
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
	const FGxItemDefinition* Definition = GetItemDefinition( DataTable , ItemId );

	if( Definition != nullptr )
	{
		return CreateInstance( Outer , Definition );
	}

	return nullptr;
}
//----------------------------------------------------------------------------------------------------------------
