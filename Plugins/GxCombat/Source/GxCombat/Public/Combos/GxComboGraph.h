// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GxComboGroup.h"

#include "GxComboGraph.generated.h"



/**
 * 
 */
UCLASS(Blueprintable)
class GXCOMBAT_API UGxComboGraph : public UObject
{
	GENERATED_BODY()


// Properties
public:

	/** Holds all Sequences defined for this ActionSet */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = "Sequences" )
	TArray<TObjectPtr<UGxComboGroup>> Groups;


#if WITH_EDITOR

	/* called by the editor when creating this asset*/
	void CreateDefaultGroup();

#endif


};
