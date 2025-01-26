// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_GxCombatBase.generated.h"

class UGxCombatComponent;
/**
 * 
 */
UCLASS()
class GXCOMBAT_API UAnimNotifyState_GxCombatBase : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UGxCombatComponent* GetOwnerCombatComponent( USkeletalMeshComponent* MeshComponent );

};
