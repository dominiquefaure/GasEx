// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "WeaponBase.h"
#include "GameFramework/Character.h"



// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh		=	CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "WeaponMesh" ) );
	ScabbardMesh	=	CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "ScabbardMesh" ) );

	IsDrawn			=	false;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void AWeaponBase::Equip( ACharacter* TargetCharacter )
{
	Super::Equip( TargetCharacter );

	if( WeaponMesh != nullptr )
	{
		WeaponMesh->AttachToComponent( TargetCharacter->GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , DrawnSocket );
	}

	if( ScabbardMesh != nullptr )
	{
		ScabbardMesh->AttachToComponent( TargetCharacter->GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , ScabbardSocket );
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void AWeaponBase::UnEquip( ACharacter* TargetCharacter )
{
	if( WeaponMesh != nullptr )
	{
		WeaponMesh->DetachFromComponent( FDetachmentTransformRules::KeepWorldTransform );
	}

	if( ScabbardMesh != nullptr )
	{
		ScabbardMesh->DetachFromComponent( FDetachmentTransformRules::KeepWorldTransform );
	}

	Super::UnEquip( TargetCharacter );
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void AWeaponBase::SetDrawnState( bool InDrawn )
{
	if( InDrawn != IsDrawn )
	{
		IsDrawn									=	InDrawn;

		if( WeaponMesh != nullptr )
		{
			if( InDrawn )
			{
				WeaponMesh->AttachToComponent( OwnerCharacter->GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , DrawnSocket );
			}
			else
			{
				WeaponMesh->AttachToComponent( OwnerCharacter->GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , ScabbardSocket );
			}
		}
	}
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
bool AWeaponBase::GetDrawnState()
{
	return IsDrawn;
}
//-----------------------------------------------------------------------------------------
