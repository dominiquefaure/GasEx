// Copyright Dominique Faure. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMappingContext.h"
#include "GxInputConfig.generated.h"

class UInputMappingContext;
class UGxInputProcessor;

UCLASS(BlueprintType, Const)
class UGxInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	/**
	 * The Input mapping context to use for this input config
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	/**
	 * Array of input processors that manage input action handling
	 * Each processor is responsible for handling one or more input actions
	 */
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	TArray<TObjectPtr<UGxInputProcessor>> InputProcessors;
};