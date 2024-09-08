// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentBase.h"
#include "WeaponBase.generated.h"

class GASEXSAMPLE_API IWeaponInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void Equip( ACharacter* TargetCharacter )=0;
	virtual void UnEquip( ACharacter* TargetCharacter )=0;

	// Draw or Stheath the Weapon 
	UFUNCTION( BlueprintCallable )
	void SetDrawnState( bool IsDrawn );

	// is the Weapon drawn or Stealth
	UFUNCTION( BlueprintCallable )
	bool GetDrawnState();

private:

	bool IsDrawn;
};
