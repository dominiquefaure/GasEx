// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "EquipmentManagerComponent.h"
#include "EquipmentActor.h"
#include "WeaponActor.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UEquipmentManagerComponent::UEquipmentManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipmentManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCharacter=	Cast<ACharacter>( GetOwner() );
}


// Called every frame
void UEquipmentManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//-----------------------------------------------------------------------------------------
bool UEquipmentManagerComponent::EquipItem( FString TargetSlot , AEquipmentActor* NewEquipment )
{
	if( EquipedItems.Contains( TargetSlot ) )
	{
		EquipedItems[TargetSlot]	=	NewEquipment;
	}
	else
	{
		EquipedItems.Add( TargetSlot , NewEquipment );
	}
	NewEquipment->Equip( OwnerCharacter );

	return true;

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
AWeaponActor* UEquipmentManagerComponent::GetWeapon( FString WeaponSlot )
{
	return Cast<AWeaponActor>( EquipedItems[WeaponSlot] );
}
//-----------------------------------------------------------------------------------------
