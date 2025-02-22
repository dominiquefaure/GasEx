// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxAttackMoveSet_Factory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor
#include "Combos/GxComboGraph.h"

//---------------------------------------------------------------------------------------------
UGxComboGraph_Factory::UGxComboGraph_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGxComboGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGxComboGraph_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGxComboGraph_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGxComboGraph::StaticClass() ) );
	UGxComboGraph* NewGraph	=	NewObject<UGxComboGraph>( InParent , UGxComboGraph::StaticClass() , InName , Flags | RF_Transactional);

	NewGraph->CreateDefaultGroup();

	return NewGraph;
}
//---------------------------------------------------------------------------------------------

