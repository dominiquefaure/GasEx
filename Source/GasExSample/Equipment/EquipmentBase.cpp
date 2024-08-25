// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "EquipmentBase.h"

// Sets default values
AEquipmentBase::AEquipmentBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEquipmentBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipmentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//-----------------------------------------------------------------------------------------
void AEquipmentBase::Equip( ACharacter* TargetCharacter )
{
	OwnerCharacter	=	TargetCharacter;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void AEquipmentBase::UnEquip( ACharacter* TargetCharacter )
{
	OwnerCharacter	=	nullptr;
}
//-----------------------------------------------------------------------------------------
