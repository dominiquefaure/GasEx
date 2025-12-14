// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "GxItemInstanceTrait.generated.h"

struct FGxItemTrait;

/*
* Base class for all itemInstance Traits
*/
USTRUCT( BlueprintType)
struct GXITEMS_API FGxItemInstanceTrait
{
	GENERATED_BODY()

    FGxItemInstanceTrait(){ }
	FGxItemInstanceTrait( const FGxItemInstanceTrait& InOther )
		: TraitDefinition( InOther.TraitDefinition )
	{
	}

	virtual void Initialize( const TInstancedStruct<FGxItemTrait>& InItemTrait );


	/* The Item Instance that owns this Trait */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = (AllowPrivateAccess) )
	TObjectPtr<class UGxItemInstance> OwnerItem;

protected:

    /* The Source Trait used to create this instance */
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    TInstancedStruct<FGxItemTrait> TraitDefinition;


};