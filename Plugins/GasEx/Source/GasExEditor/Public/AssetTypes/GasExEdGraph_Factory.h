// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GasExEdGraph_Factory.generated.h"

/**
 * 
 */
UCLASS( )
class GASEXEDITOR_API UGasExEdGraph_Factory : public UFactory
{
	GENERATED_BODY()
	
public:

	UGasExEdGraph_Factory();

	// The type of blueprint that will be created
	UPROPERTY( EditAnywhere , Category=GasEx )
	TEnumAsByte<enum EBlueprintType> BlueprintType;

	// Allow to place the asset into dedicated category when try to add new asset
	//	virtual uint32 GetMenuCategories() const override;

	// Creates the asset inside the UE4 Editor
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override;


};
