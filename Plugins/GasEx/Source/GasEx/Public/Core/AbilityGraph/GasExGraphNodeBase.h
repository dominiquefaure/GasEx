// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasExGraphNodeBase.generated.h"

class UGasExGraphLink;

/**
 * 
 */
UCLASS()
class GASEX_API UGasExGraphNodeBase : public UObject
{
	GENERATED_BODY()


public:
	
	// links to the next actions possibles
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly)
	TArray<UGasExGraphLink*> Links;

public:

	// add a new Link to an Action node to play after this one
	void AddLink( UGasExGraphNodeBase* NextNode );
};
