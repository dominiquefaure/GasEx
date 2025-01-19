// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxWeaponHitComponent.h"
#include "HitDetection/GxHitDetectionTrace.h"

// Sets default values for this component's properties
UGxWeaponHitComponent::UGxWeaponHitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UGxWeaponHitComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Owner	=	GetOwner();
	for( UGxHitDetectionBase* Element : HitCollisionElements )
	{
		Element->Setup( Owner );
	}

}


// Called every frame
void UGxWeaponHitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	TArray<FHitResult> HitResults;
/*	for( TSubclassOf<UGxHitDetectionBase>& HitElement : HitCollisionElements )
	{
		HitElement->PerformHitDetection( HitResults );
	}
	*/
	for( int i = 0; i < HitCollisionElements.Num(); i++ )
	{
		HitCollisionElements[i]->PerformHitDetection( HitResults , DebugSettings );
	}
}

