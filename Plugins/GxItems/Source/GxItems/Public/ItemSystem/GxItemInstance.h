// Copyright Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "GxItemInstance.generated.h"

class UGxItem;
struct FGxItemInstanceTrait;

UCLASS( BlueprintType )
class GXITEMS_API UGxItemInstance : public UObject
{
	GENERATED_BODY()

public:

	/* Initialize the Instance of an Item */
	virtual void Initialize( UGxItem* InItemDefinition );

	AActor* GetOwningActor() const;

	template<typename T> T* GetTrait()
	{
		for( FInstancedStruct& Trait : ItemTraits )
		{
			if( T* CastedTrait = Trait.GetMutablePtr<T>() )
			{
				return CastedTrait;
			}
		}
		return nullptr;
	}

protected:

	/* Reference to the data asset that describes this Item. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess) )
	UGxItem* ItemDefinition;

	/* The Instanced version of the Different Traits of the Item*/
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess) )
	TArray<FInstancedStruct> ItemTraits;

};