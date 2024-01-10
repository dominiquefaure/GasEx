// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GasExEdAbilitySet_Factory.generated.h"

/**
 * 
 */
UCLASS( )
class GASEXEDITOR_API UGasExEdAbilitySet_Factory : public UFactory
{
	GENERATED_BODY()
	
public:

	UGasExEdAbilitySet_Factory();

	// The type of blueprint that will be created
	UPROPERTY( EditAnywhere , Category=GameplayAbilitiesFactory )
	TEnumAsByte<enum EBlueprintType> BlueprintType;

	// Allow to place the asset into dedicated category when try to add new asset
	//	virtual uint32 GetMenuCategories() const override;

	// Creates the asset inside the UE4 Editor
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override;


};
