// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GxAnimNotifyState_ChainAction.generated.h"

class UGxActionComponent;

/**
 * 
 */
UCLASS()
class GXACTIONS_API UGxAnimNotifyState_ChainAction : public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	FString WindowName;

	// Notify overrides
	virtual void NotifyBegin( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference ) override;
	virtual void NotifyEnd( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference ) override;

protected:

	UGxActionComponent* GetOwnerActionComponent( USkeletalMeshComponent* MeshComponent );

};
