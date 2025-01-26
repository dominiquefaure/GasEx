// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#include "GxHitComponentVisualizer.h"
#include "GxCombat/Public/GxHitComponent.h"

//---------------------------------------------------------------------------------------------
FGxHitComponentVisualizer::FGxHitComponentVisualizer()
{
	UMaterial* GizmoMaterial = (UMaterial*)StaticLoadObject( UMaterial::StaticClass(),NULL,TEXT("/Engine/EditorMaterials/LevelTransformMaterial.LevelTransformMaterial") );
	BoxMaterial = UMaterialInstanceDynamic::Create( GizmoMaterial, NULL );

}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxHitComponentVisualizer::DrawVisualization( const UActorComponent* Component , const FSceneView* View , FPrimitiveDrawInterface* PDI )
{
	// Draw a visualization here using PDI (or Canvas if using DrawVisualizationHUD)

	const UGxHitComponent* MyComponent = Cast<UGxHitComponent>( Component );
	if( !MyComponent )
	{
		return;
	}
//	PDI->DrawLine( FVector( 10 , 10 , 10 ) , FVector( 100 , 100 , 10 ) , FLinearColor::Blue , SDPG_World );
	//PDI->DrawPoint( FVector( 10 , 10 , 10 ) , FLinearColor::Blue, 50.0f , SDPG_World  );

	FVector Location	=	MyComponent->GetOwner()->GetActorLocation();
//	FMatrix Transform	=	FMatrix::Identity;
	FVector BoxExtend	=	FVector( 50,50,50);

	FTransform Transform=	FTransform::Identity;
	Transform.SetLocation( Location );
//	DrawBox( PDI , Transform.ToMatrixNoScale() , BoxExtend , BoxMaterial->GetRenderProxy() , SDPG_World);
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void FGxHitComponentVisualizer::DrawVisualizationHUD( const UActorComponent* Component , const FViewport* Viewport , const FSceneView* View , FCanvas* Canvas )
{
	// Draw a visualization here using PDI (or Canvas if using DrawVisualizationHUD)

	//  PDI->DrawPoint( FVector( 10 , 10 , 10 ) , FLinearColor::Blue, 50.0f , 0  );
}
//---------------------------------------------------------------------------------------------
