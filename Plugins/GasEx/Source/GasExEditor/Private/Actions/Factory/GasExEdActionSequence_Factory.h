// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GasExEdActionSequence_Factory.generated.h"

/**
 * 
 */
UCLASS( )
class GASEXEDITOR_API UGasExEdActionSequence_Factory : public UFactory
{
	GENERATED_BODY()
	
public:

	UGasExEdActionSequence_Factory();

	// The type of blueprint that will be created
	UPROPERTY( EditAnywhere , Category=GasEx )
	TEnumAsByte<enum EBlueprintType> BlueprintType;

	// Allow to place the asset into dedicated category when try to add new asset
	//	virtual uint32 GetMenuCategories() const override;

	// Creates the asset inside the UE4 Editor
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override;


};
