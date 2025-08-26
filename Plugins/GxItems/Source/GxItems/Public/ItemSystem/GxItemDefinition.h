// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "GameplayTagContainer.h"
#include "GxItemTrait.h"
#include "GxItemDefinition.generated.h"


class UGxItemInstance;

USTRUCT( BlueprintType , Category = "GxItems" )
struct GXITEMS_API FGxItemDefinition
{
	GENERATED_BODY()

#pragma region "Properties"

	// Class to spawn
	UPROPERTY(EditDefaultsOnly , Category = Equipment)
	TSubclassOf<UGxItemInstance> InstanceType;

	// unique name for the identifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TInstancedStruct<FGxItemTrait>> Traits;

#pragma endregion

	FGxItemDefinition();

	/**
	 * Creates a new instance of this item definition.
	 * @param Outer The outer object for the new instance.
	 * @return A new instance of UGxItemInstance or nullptr if InstanceType is not set.
	 */
	UGxItemInstance* CreateInstance( UObject* Outer ) const;


	virtual TSubclassOf<UGxItemInstance> GetInstanceClass() const;

};