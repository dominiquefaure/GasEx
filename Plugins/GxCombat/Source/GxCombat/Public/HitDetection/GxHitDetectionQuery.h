// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GxHitDetectionBase.h"
#include "GxHitDetectionStructs.h"
#include "GxHitDetectionQuery.generated.h"


UENUM( BlueprintType )
enum class EGxHitDetectionQueryMode : uint8
{
	Trace = 0,
	Sweep,
};

UENUM( BlueprintType )
enum class EGxHitDetectionQueryType : uint8
{
	Channel = 0 UMETA( DisplayName = "Perform the Qery per Channel" ) ,
	Profile UMETA( DisplayName = "Perform the Query per Profile" ) ,
	Object UMETA( DisplayName = "Perform the Query per Objets type" )
};


USTRUCT( BlueprintType )
struct FGxHitDetectionQueryMethod
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Mode of query to evaluate the hit collision" ) )
	EGxHitDetectionQueryMode QueryMode;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = ( DisplayName = "Type of query to evaluate the hit collision" ) )
	EGxHitDetectionQueryType QueryType;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , meta = ( Tooltip = "In case you trace by channel." , EditCondition = "QueryType == EGxHitDetectionQueryType::Channel" , EditConditionHides ) )
	TEnumAsByte<ETraceTypeQuery> TraceChannel = UEngineTypes::ConvertToTraceType( ECC_Visibility );

	UPROPERTY( EditAnywhere , BlueprintReadWrite , meta = ( Tooltip = "In case you trace by Profile." , EditCondition = "QueryType == EGxHitDetectionQueryType::Profile" , EditConditionHides ) )
	FName ProfileName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , meta = ( Tooltip = "In case you trace by Objects." , EditCondition = "QueryType == EGxHitDetectionQueryType::Object" , EditConditionHides ) )
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;

};

/**
 * 
 */
UCLASS( EditInlineNew )
class GXCOMBAT_API UGxHitDetectionQuery : public UGxHitDetectionBase
{
	GENERATED_BODY()

public:

	/*The Shape to use for Hit Detection*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly  )
	FGxHitDetectionShape Shape;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGxHitDetectionQueryMethod QueryMethod;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGxHitDetectionAnchor Anchor;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = KismetTraceSettings )
	bool AllowMultiTrace = false;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = KismetTraceSettings  )
	bool UseComplexTrace = false;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = KismetTraceSettings , meta = ( Tooltip = "True means it will ignore self." ) )
	bool bIgnoreSelf = true;

	virtual bool PerformHitDetection( TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors )override;

private: 

	bool PerformAbsoluteHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformSocketsHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors );

	bool PerformHitDetection( const FVector& InLocation, TArray<FHitResult>& OutHits , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformHitDetectionSingle( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformHitDetectionMulti( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );

	bool PerformTraceSingleByChannel( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformTraceSingleByProfile( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformTraceSingleForObjects( const FVector& InLocation , FHitResult& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );

	bool PerformTraceMultiByChannel( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformTraceMultiByProfile( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );
	bool PerformTraceMultiForObjects( const FVector& InLocation , TArray<FHitResult>& OutResult , TArray<TObjectPtr<AActor>> IgnoredActors );


	void GenerateSocketInstances();

	UPROPERTY()
	TArray<FGxHitDetectionQueryInstance> Sockets;

};
