// Copyright 2023-2025 Dominique Faure. All Rights Reserved.


#include "GxHitComponent.h"
#include "HitDetection/GxHitDetectionBase.h"

// Sets default values for this component's properties
//-----------------------------------------------------------------------------------------
UGxHitComponent::UGxHitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

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
}
//-----------------------------------------------------------------------------------------

