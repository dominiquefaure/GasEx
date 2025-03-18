// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "AssetType/GxActionGraph_Factory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor
#include "ActionGraph/GxActionGraph.h"

//---------------------------------------------------------------------------------------------
UGxActionGraph_Factory::UGxActionGraph_Factory()
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UGxActionGraph::StaticClass();
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UGxActionGraph_Factory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UGxActionGraph_Factory::FactoryCreateNew( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , UObject* Context , FFeedbackContext* Warn )
{
	check( InClass->IsChildOf( UGxActionGraph::StaticClass() ) );
	UGxActionGraph* NewGraph	=	NewObject<UGxActionGraph>( InParent , UGxActionGraph::StaticClass() , InName , Flags | RF_Transactional);

	NewGraph->CreateDefaultGroup();

	return NewGraph;
}
//---------------------------------------------------------------------------------------------

