// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Interactions/GasExInteractibleActor.h"

// Sets default values
AGasExInteractibleActor::AGasExInteractibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGasExInteractibleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGasExInteractibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

