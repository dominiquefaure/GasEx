// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Actions/Factory/GasExEdActionDataTable_Factory.h"

#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Actions/GasExActionDataTable.h"


//---------------------------------------------------------------------------------------------
UGasExEdActionDataTable_Factory::UGasExEdActionDataTable_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGasExActionDataTable::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGasExEdActionDataTable_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGasExEdActionDataTable_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGasExActionDataTable::StaticClass() ) );
	return NewObject<UObject>( InParent , InClass , InName , Flags | RF_Transactional );

}
//---------------------------------------------------------------------------------------------
