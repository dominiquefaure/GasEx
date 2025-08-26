// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "ItemSystem/GxItemTrait.h"
#include "GxEquipmentManagerComponent.generated.h"

UCLASS( ClassGroup = (GxItems) , meta = (BlueprintSpawnableComponent) )
class GXITEMS_API UGxEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGxEquipmentManagerComponent();

	/** Equip an item instance */
	UFUNCTION( BlueprintCallable , Category = "GxItems|Equipment" )
	virtual bool EquipItem( class UGxItemInstance* ItemInstance );

	/** Unequip an item instance */
	UFUNCTION( BlueprintCallable , Category = "GxItems|Equipment" )
	virtual void UnequipItem( class UGxItemInstance* ItemInstance );

};