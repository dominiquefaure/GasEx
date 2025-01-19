// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GxHitDetectionBase.h"
#include "GxHitDetectionStructs.h"
#include "GxHitDetectionTrace.generated.h"


UENUM( BlueprintType )
enum class EGxHitDetectionQueryType : uint8
{
	Channel = 0 UMETA( DisplayName = "Perform the Qery per Channel" ) ,
	Profile UMETA( DisplayName = "Perform the Query per Profile" ) ,
	Object UMETA( DisplayName = "Perform the Query per Objets type" )
};


USTRUCT( BlueprintType )
struct FGxHitDetectionQuery
{
	GENERATED_BODY()

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
class GXCOMBAT_API UGxHitDetectionTrace : public UGxHitDetectionBase
{
	GENERATED_BODY()

public:

	/*The Shape to use for Hit Detection*/
	UPROPERTY( EditAnywhere , BlueprintReadOnly  )
	FGxHitDetectionShape Shape;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGxHitDetectionQuery Query;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	FGxHitDetectionAnchor Anchor;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = KismetTraceSettings )
	bool AllowMultiTrace = false;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = KismetTraceSettings  )
	bool UseComplexTrace = false;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = KismetTraceSettings , meta = ( Tooltip = "True means it will ignore self." ) )
	bool bIgnoreSelf = true;

	virtual void PerformHitDetection( TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings )override;

private: 

	bool PerformAbsoluteHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformSocketsHitDetection( const FVector& InActorLocation , TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );

	bool PerformHitDetection( const FVector& InLocation, TArray<FHitResult>& OutHits , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformHitDetectionSingle( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformHitDetectionMulti( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );

	bool PerformTraceSingleByChannel( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformTraceSingleByProfile( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformTraceSingleForObjects( const FVector& InLocation , FHitResult& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );

	bool PerformTraceMultiByChannel( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformTraceMultiByProfile( const FVector& InLocation , TArray<FHitResult>& OutResult, FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );
	bool PerformTraceMultiForObjects( const FVector& InLocation , TArray<FHitResult>& OutResult , FGxHitDetectionKismetDebugDrawSettings& InDebugDrawSettings );


	void GenerateSocketInstances();

	UPROPERTY()
	TArray< FGxHitDetectionSocketInstance> Sockets;

};
