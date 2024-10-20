// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/Factory/GasExEdActionSet_Factory.h"

#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Actions/GasExActionSet.h"


//---------------------------------------------------------------------------------------------
UGasExEdActionSet_Factory::UGasExEdActionSet_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGasExActionSet::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExEdActionSet_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGasExEdActionSet_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGasExActionSet::StaticClass() ) );
	return NewObject<UObject>( InParent , InClass , InName , Flags | RF_Transactional );

}
//---------------------------------------------------------------------------------------------
