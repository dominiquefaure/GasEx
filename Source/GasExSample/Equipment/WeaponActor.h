// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentActor.h"

#include "GxHitComponent.h"

#include "WeaponActor.generated.h"

UCLASS()
class GASEXSAMPLE_API AWeaponActor : public AEquipmentActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponActor();


	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	USkeletalMeshComponent* ScabbardMesh;


	UPROPERTY( EditAnywhere )
	FName DrawnSocket;

	UPROPERTY( EditAnywhere )
	FName ScabbardSocket;

	// Draw or Stheath the Weapon 
	UFUNCTION( BlueprintCallable )
	void SetDrawnState( bool IsDrawn );

	// is the Weapon drawn or Stealth
	UFUNCTION( BlueprintCallable )
	bool GetDrawnState();

	UFUNCTION( BlueprintCallable )
	UGxHitComponent* GetHitComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;


	virtual void Equip( ACharacter* TargetCharacter )override;
	virtual void UnEquip( ACharacter* TargetCharacter )override;


private:

	bool IsDrawn;
};
