// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GxActionInputBuffer.generated.h"



USTRUCT()
struct GXACTIONS_API FGxActionInputBuffer
{
	GENERATED_BODY()

	TArray<FGameplayTag>					InputBuffer;
//	TQueue<FGameplayTag>					InputQueue;

	void OnKeyPressed( FGameplayTag InputKey );

	void ClearInputs();


	bool IsEmpty() const;

	const FGameplayTag GetInputTag( bool InConsume = true );
};

