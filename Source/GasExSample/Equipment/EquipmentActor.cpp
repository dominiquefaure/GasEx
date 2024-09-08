// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "EquipmentActor.h"

// Sets default values
AEquipmentActor::AEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEquipmentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//-----------------------------------------------------------------------------------------
void AEquipmentActor::Equip( ACharacter* TargetCharacter )
{
	OwnerCharacter	=	TargetCharacter;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void AEquipmentActor::UnEquip( ACharacter* TargetCharacter )
{
	OwnerCharacter	=	nullptr;
}
//-----------------------------------------------------------------------------------------
