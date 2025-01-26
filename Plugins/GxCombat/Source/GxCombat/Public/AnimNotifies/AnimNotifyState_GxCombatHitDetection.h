// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_GxCombatBase.h"
#include "GxCombatEnums.h"
#include "AnimNotifyState_GxCombatHitDetection.generated.h"

class UGxCombatComponent;
/**
 *
 */
UCLASS()
class GXCOMBAT_API UAnimNotifyState_GxCombatHitDetection : public UAnimNotifyState_GxCombatBase
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere )
	EGxCollisionSource Source;

	UPROPERTY( EditAnywhere )
	FString CollisionFilter;

	// Notify overrides
	virtual void NotifyBegin( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , float TotalDuration , const FAnimNotifyEventReference& EventReference ) override;
	virtual void NotifyEnd( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation , const FAnimNotifyEventReference& EventReference ) override;
};
