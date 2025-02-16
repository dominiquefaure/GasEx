// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxAttackMoveSet_Factory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor
#include "Attacks/GxAttackMoveSet.h"

//---------------------------------------------------------------------------------------------
UGxAttackMoveSet_Factory::UGxAttackMoveSet_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGxAttackMoveSet::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGxAttackMoveSet_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGxAttackMoveSet_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGxAttackMoveSet::StaticClass() ) );
	return NewObject<UObject>( InParent , InClass , InName , Flags | RF_Transactional );

}
//---------------------------------------------------------------------------------------------

