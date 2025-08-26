// Copyright Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "GxItemInstance.generated.h"


struct FGxItemDefinition;
struct FGxItemInstanceTrait;

UCLASS( BlueprintType )
class GXITEMS_API UGxItemInstance : public UObject
{
	GENERATED_BODY()

public:

    /* Initialize the Instance of an Item */
//	virtual void Initialize( const TInstancedStruct<FGxItemDefinition>& InItemDefinition );

	virtual void Initialize( const FGxItemDefinition& InItemDefinition );

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

    /* The static data that describes this Item. */
    UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    TInstancedStruct<FGxItemDefinition> ItemDefinition;

    /* The Instanced version of the Different Traits of the Item*/
    UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
//	TArray<TInstancedStruct<FGxItemInstanceTrait>> ItemTraits;
	TArray<FInstancedStruct> ItemTraits;

};