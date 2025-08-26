// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "ItemSystem/GxItemTrait.h"
#include "GxItemTrait_Equipment.generated.h"


USTRUCT()
struct FEquipmentActorToSpawn
{
	GENERATED_BODY()

	FEquipmentActorToSpawn(){}

	UPROPERTY(EditAnywhere, Category=Equipment)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FName AttachSocket;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FTransform AttachTransform;
};


/*
* Base class for all iterms Traits
*/
USTRUCT( BlueprintType)
struct GXITEMS_API FGxItemTrait_Equipment : public FGxItemTrait
{
	GENERATED_BODY()

	// Actors to spawn on the pawn when this is equipped
	UPROPERTY( EditAnywhere , Category = Equipment )
	TArray<FEquipmentActorToSpawn> ActorsToSpawn;


	virtual const UScriptStruct* GetInstanceScriptStruct() const override;

};