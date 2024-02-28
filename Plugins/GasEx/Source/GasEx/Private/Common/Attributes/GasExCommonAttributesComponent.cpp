// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "Common/Attributes/GasExCommonAttributesComponent.h"
#include "Common/Attributes/GasExCommonAttributeSet.h"
#include "Core/AbilitySystem/GasExAbilitySystemComponent.h"

#include "GameplayEffectExtension.h"


//-----------------------------------------------------------------------------------------
static AActor* GetInstigatorFromAttrChangeData(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.GEModData != nullptr)
	{
		const FGameplayEffectContextHandle& EffectContext = ChangeData.GEModData->EffectSpec.GetEffectContext();
		return EffectContext.GetOriginalInstigator();
	}

	return nullptr;
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Sets default values for this component's properties
UGasExCommonAttributesComponent::UGasExCommonAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called when the game starts
void UGasExCommonAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UGasExAbilitySystemComponent* ASC	=	GetOwner()->GetComponentByClass<UGasExAbilitySystemComponent>();

	LinkToAbilitySystem(ASC);
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
// Called every frame
void UGasExCommonAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
float UGasExCommonAttributesComponent::GetHealth() const
{
	return (CommonAttributeSet ? CommonAttributeSet->GetHealth() : 0.0f);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
float UGasExCommonAttributesComponent::GetMaxHealth() const
{
	return (CommonAttributeSet ? CommonAttributeSet->GetMaxHealth() : 0.0f);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
float UGasExCommonAttributesComponent::GetStamina() const
{
	return (CommonAttributeSet ? CommonAttributeSet->GetStamina() : 0.0f);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
float UGasExCommonAttributesComponent::GetMaxStamina() const
{
	return (CommonAttributeSet ? CommonAttributeSet->GetMaxStamina() : 0.0f);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributesComponent::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(this , Data.OldValue , Data.NewValue , GetInstigatorFromAttrChangeData(Data));
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributesComponent::OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(this , Data.OldValue , Data.NewValue , GetInstigatorFromAttrChangeData(Data));
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributesComponent::OnStaminaAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnStaminaChanged.Broadcast(this , Data.OldValue , Data.NewValue , GetInstigatorFromAttrChangeData(Data));
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
void UGasExCommonAttributesComponent::OnMaxStaminaAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnMaxStaminaChanged.Broadcast(this , Data.OldValue , Data.NewValue , GetInstigatorFromAttrChangeData(Data));
}
//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------
void UGasExCommonAttributesComponent::LinkToAbilitySystem(UGasExAbilitySystemComponent* ASC)
{

	AbilitySystemComponent = ASC;

	CommonAttributeSet = AbilitySystemComponent->GetSet<UGasExCommonAttributeSet>();

	if (CommonAttributeSet == nullptr)
	{
		AActor* Owner = GetOwner();
		UE_LOG(LogTemp , Error , TEXT("UGasExCommonAttributesComponent: Cannot initialize Common Attribute component for owner [%s] Default attribute table not set correctly.") , *GetNameSafe(Owner));
	}

	if (AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CommonAttributeSet->GetHealthAttribute()).AddUObject(this , &UGasExCommonAttributesComponent::OnHealthAttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CommonAttributeSet->GetMaxHealthAttribute()).AddUObject(this , &UGasExCommonAttributesComponent::OnMaxHealthAttributeChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CommonAttributeSet->GetStaminaAttribute()).AddUObject(this , &UGasExCommonAttributesComponent::OnStaminaAttributeChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CommonAttributeSet->GetMaxStaminaAttribute()).AddUObject(this , &UGasExCommonAttributesComponent::OnMaxStaminaAttributeChanged);
	}
}
//-----------------------------------------------------------------------------------------
