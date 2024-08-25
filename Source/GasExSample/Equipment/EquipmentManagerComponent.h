// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentManagerComponent.generated.h"


class ACharacter;
class AEquipmentBase;
class AWeaponBase;

USTRUCT()
struct FEquipmentSlot
{
	GENERATED_BODY()
		
	UPROPERTY( EditAnywhere )
	FString Name;

	// socket to use when the Equipment is not drawn
	UPROPERTY( EditAnywhere )
	FName SthealthSocket;

	// socket to use when the Equipment is drawn , only for weapon types
	UPROPERTY( EditAnywhere )
	FName DrawnSocket;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASEXSAMPLE_API UEquipmentManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentManagerComponent();

	UPROPERTY(EditAnywhere)
	TArray<FEquipmentSlot> Slots;



public:

	// Try to equip a new Item
	UFUNCTION(BlueprintCallable)
	bool EquipItem( FString TargetSlot , AEquipmentBase* NewEquipment );

	// Get the Weapon present at the given Slot
	UFUNCTION( BlueprintCallable )
	AWeaponBase* GetWeapon( FString WeaponSlot );

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	ACharacter* OwnerCharacter;

	TMap<FString,AEquipmentBase*> EquipedItems;


};
