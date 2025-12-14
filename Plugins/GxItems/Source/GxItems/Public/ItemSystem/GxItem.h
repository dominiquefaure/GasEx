// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "GameplayTagContainer.h"
#include "GxItemTrait.h"
#include "GxItem.generated.h"


class UGxItemInstance;

UCLASS( BlueprintType , Category = "GxItems" )
class GXITEMS_API UGxItem : public UDataAsset
{
	GENERATED_BODY()

public:

#pragma region "Properties"

	// unique name for the identifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TInstancedStruct<FGxItemTrait>> Traits;

#pragma endregion

	UGxItem();

	/**
	 * Creates a new instance of this item.
	 * @param Outer The outer object for the new instance.
	 * @return A new instance of UGxItemInstance or nullptr if InstanceType is not set.
	 */
	UGxItemInstance* CreateInstance( UObject* Outer );


	virtual TSubclassOf<UGxItemInstance> GetInstanceClass() const;

};