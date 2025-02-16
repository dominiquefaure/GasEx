// Copyright 2023-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class GXCOMBATEDITOR_API FxAttackMoveSet_AssetTypeActions : public FAssetTypeActions_Base
{
public:
	FxAttackMoveSet_AssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	//~ IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	//virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;

private:
	EAssetTypeCategories::Type AssetCategory;
};
