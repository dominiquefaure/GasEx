// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitDetection/GxHitDetectionBase.h"
#include "GxWeaponHitComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GXCOMBAT_API UGxWeaponHitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGxWeaponHitComponent();

	UPROPERTY( EditAnywhere , Instanced ,BlueprintReadWrite )
	TArray<UGxHitDetectionBase*> HitCollisionElements;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGxHitDetectionKismetDebugDrawSettings DebugSettings;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
