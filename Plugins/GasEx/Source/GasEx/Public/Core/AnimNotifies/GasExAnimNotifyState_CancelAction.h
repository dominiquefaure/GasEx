// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GasExAnimNotifyState_CancelAction.generated.h"

class UGasExActionSystemComponent;

/**
 * 
 */
UCLASS()
class GASEX_API UGasExAnimNotifyState_CancelAction : public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	FString WindowName;

	// Notify overrides
	virtual void NotifyBegin( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference ) override;
	virtual void NotifyEnd( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference ) override;

protected:

	UGasExActionSystemComponent* GetOwnerActionComponent( USkeletalMeshComponent* MeshComponent );

};
