// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentBase.h"
#include "WeaponBase.generated.h"

UCLASS()
class GASEXSAMPLE_API AWeaponBase : public AEquipmentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();


	UPROPERTY( EditAnywhere )
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY( EditAnywhere )
	USkeletalMeshComponent* ScabbardMesh;


	UPROPERTY( EditAnywhere )
	FName DrawnSocket;

	UPROPERTY( EditAnywhere )
	FName ScabbardSocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;


	virtual void Equip( ACharacter* TargetCharacter )override;
	virtual void UnEquip( ACharacter* TargetCharacter )override;

	// Draw or Stheath the Weapon 
	UFUNCTION( BlueprintCallable )
	void SetDrawnState( bool IsDrawn );

	// is the Weapon drawn or Stealth
	UFUNCTION( BlueprintCallable )
	bool GetDrawnState();

private:

	bool IsDrawn;
};
