// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/GasExEdAbilitySet_Factory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Core/AbilitySystem/GasExAbilitySet.h"


//---------------------------------------------------------------------------------------------
UGasExEdAbilitySet_Factory::UGasExEdAbilitySet_Factory(  )
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGasExAbilitySet::StaticClass();
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
bool UGasExEdAbilitySet_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGasExEdAbilitySet_Factory::FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGasExAbilitySet::StaticClass() ) );
	return NewObject<UObject>( InParent , InClass , InName , Flags | RF_Transactional );

}
//---------------------------------------------------------------------------------------------

