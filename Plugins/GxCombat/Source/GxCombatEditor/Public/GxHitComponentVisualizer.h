// Copyright 2023-2025 Dominique Faure. All Rights Reserved.

#pragma once

#include "ComponentVisualizer.h"

class FGxHitComponentVisualizer : public FComponentVisualizer
{
public:

    FGxHitComponentVisualizer();

    // Override this to draw in the scene
    virtual void DrawVisualization( const UActorComponent* Component , const FSceneView* View ,
                                    FPrimitiveDrawInterface* PDI ) override;

    // Override this to draw on the editor's viewport
    virtual void DrawVisualizationHUD( const UActorComponent* Component , const FViewport* Viewport ,
                                       const FSceneView* View , FCanvas* Canvas ) override;


private:
    TObjectPtr<UMaterialInstanceDynamic> BoxMaterial;

};