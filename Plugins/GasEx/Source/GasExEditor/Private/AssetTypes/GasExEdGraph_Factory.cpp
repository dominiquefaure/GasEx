// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/GasExEdGraph_Factory.h"

#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Core/AbilityGraph/GasExGraph.h"


//---------------------------------------------------------------------------------------------
UGasExEdGraph_Factory::UGasExEdGraph_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGasExGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------
/*
//---------------------------------------------------------------------------------------------
uint32 UEGSActionGraphFactory::GetMenuCategories() const
{
//Let's place this asset in the Blueprints category in the Editor
return EAssetTypeCategories::Blueprint;
}
//---------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------
bool UGasExEdGraph_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGasExEdGraph_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGasExGraph::StaticClass() ) );
	return NewObject<UObject>( InParent , InClass , InName , Flags | RF_Transactional );

}
//---------------------------------------------------------------------------------------------