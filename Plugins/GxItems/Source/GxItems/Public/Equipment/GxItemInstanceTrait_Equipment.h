// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "ItemSystem/GxItemTrait.h"
#include "ItemSystem/GxItemInstanceTrait.h"
#include "GxItemInstanceTrait_Equipment.generated.h"


USTRUCT()
struct FGxItemInstanceTrait_Equipment : public FGxItemInstanceTrait
{
	GENERATED_BODY()

public:

	UPROPERTY( VisibleAnywhere)
	bool bIsEquipped = false;

	// called when the Item is Equipped/Unequiped
	virtual void OnEquip();
	virtual void OnUnEquip();


private:
	
	APawn* GetOwnerPawn() const;

private:

	TArray<AActor*> SpawnedActors;


};