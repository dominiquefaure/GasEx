// Copyright 2023-2025 Dominique Faure. All Rights Reserved.


#include "GxHitComponent.h"
#include "HitDetection/GxHitDetectionBase.h"

// Sets default values for this component's properties
//-----------------------------------------------------------------------------------------
UGxHitComponent::UGxHitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGxHitComponent::SetHitDetectionEnable( bool InEnable )
{
	SetComponentTickEnabled( InEnable );
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called when the game starts
void UGxHitComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Owner	=	GetOwner();
	for( UGxHitDetectionBase* Element : HitCollisionElements )
	{
		Element->Setup( Owner );
	}

	SetHitDetectionEnable( false );
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called every frame
void UGxHitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
//-----------------------------------------------------------------------------------------

