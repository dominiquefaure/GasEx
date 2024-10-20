// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasExActionSequence.h"

#include "GasExActionSet.generated.h"

USTRUCT( BlueprintType )
struct GASEX_API FGasExActionSequenceDesc
{
	GENERATED_BODY()
		
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	TObjectPtr<UGasExActionSequence> Sequence;

	/** can This Sequence break others on going Sequence? **/
	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	bool CanBreakSequences;

};


/**
 * 
 */
UCLASS(Blueprintable)
class GASEX_API UGasExActionSet : public UObject
{
	GENERATED_BODY()


// Properties
public:

	/** Holds all Sequences defined for this ActionSet */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Sequences" )
	TArray<FGasExActionSequenceDesc> Sequences;


};
