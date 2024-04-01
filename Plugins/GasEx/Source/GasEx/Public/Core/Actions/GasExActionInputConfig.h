// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GasExActionInputConfig.generated.h"

class UInputAction;


USTRUCT( BlueprintType )
struct FGasExInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly )
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Meta = ( Categories = "InputTag" ) )
	FGameplayTag InputTag;
};



UCLASS( BlueprintType , Const )
class UGasExInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:



	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Meta = ( TitleProperty = "InputAction" ) )
	TArray<FGasExInputAction> InputActions;

};