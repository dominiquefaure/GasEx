// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitDetection/GxHitDetectionBase.h"
#include "GxHitComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GXCOMBAT_API UGxHitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGxHitComponent();

	UPROPERTY( EditAnywhere , Instanced ,BlueprintReadWrite )
	TArray<UGxHitDetectionBase*> HitCollisionElements;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



private:

};
