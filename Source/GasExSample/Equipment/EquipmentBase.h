// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentBase.generated.h"

UCLASS()
class GASEXSAMPLE_API AEquipmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentBase();

	UFUNCTION()
		virtual void Equip( ACharacter* TargetCharacter );

	UFUNCTION()
		virtual void UnEquip( ACharacter* TargetCharacter );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	ACharacter* OwnerCharacter;

};