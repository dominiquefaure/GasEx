// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/Factory/GasExEdActionSequence_Factory.h"

#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Actions/GasExActionSequence.h"


//---------------------------------------------------------------------------------------------
UGasExEdActionSequence_Factory::UGasExEdActionSequence_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGasExActionSequence::StaticClass();
}
//---------------------------------------------------------------------------------------------
/*
//---------------------------------------------------------------------------------------------
uint32 UGasExEdActionSequence_Factory::GetMenuCategories() const
{
//Let's place this asset in the Blueprints category in the Editor
return EAssetTypeCategories::Blueprint;
}
//---------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------
bool UGasExEdActionSequence_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGasExEdActionSequence_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGasExActionSequence::StaticClass() ) );
	return NewObject<UObject>( InParent , InClass , InName , Flags | RF_Transactional );

}
//---------------------------------------------------------------------------------------------
