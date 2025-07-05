// Copyright 2023-2024 Dominique Faure. All Rights Reserved.


#include "GxMoverInputProducerComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "MoverComponent.h"
#include "InputAction.h"


// Sets default values for this component's properties
UGxMoverInputProducerComponent::UGxMoverInputProducerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGxMoverInputProducerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	RegisterInputs( );

	// check if we have a Mover component
	UMoverComponent* MoverComponent = GetOwner()->FindComponentByClass<UMoverComponent>();
	bUseMover	=	( MoverComponent != nullptr );
}


// Called every frame
void UGxMoverInputProducerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	// ...
	APawn* OwnerPawn	=	Cast<APawn>( GetOwner());

	// Spin camera based on input
	if (APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController()))
	{
		// Simple input scaling. A real game will probably map this to an acceleration curve
		static float LookRateYaw = 100.f;	// degs/sec
		static float LookRatePitch = 100.f;	// degs/sec

		PC->AddYawInput(CachedLookInput.Yaw * LookRateYaw * DeltaTime);
		PC->AddPitchInput(-CachedLookInput.Pitch * LookRatePitch * DeltaTime);
	}

	// Clear all camera-related cached input
	CachedLookInput = FRotator::ZeroRotator;


}

void UGxMoverInputProducerComponent::RegisterInputs()
{
	UInputComponent* PlayerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// Setup some bindings - we are currently using Enhanced Input and just using some input actions assigned in editor for simplicity
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{	
		Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &UGxMoverInputProducerComponent::OnMoveTriggered);
		Input->BindAction(MoveInputAction, ETriggerEvent::Completed, this, &UGxMoverInputProducerComponent::OnMoveCompleted);
		Input->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &UGxMoverInputProducerComponent::OnLookTriggered);
		Input->BindAction(LookInputAction, ETriggerEvent::Completed, this, &UGxMoverInputProducerComponent::OnLookCompleted);
		Input->BindAction(JumpInputAction, ETriggerEvent::Started, this, &UGxMoverInputProducerComponent::OnJumpStarted);
		Input->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &UGxMoverInputProducerComponent::OnJumpReleased);
		Input->BindAction(FlyInputAction, ETriggerEvent::Triggered, this, &UGxMoverInputProducerComponent::OnFlyTriggered);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}


void UGxMoverInputProducerComponent::OnMoveTriggered(const FInputActionValue& Value)
{
	const FVector MovementVector = Value.Get<FVector>();
	CachedMoveInputIntent.X = FMath::Clamp(MovementVector.X, -1.0f, 1.0f);
	CachedMoveInputIntent.Y = FMath::Clamp(MovementVector.Y, -1.0f, 1.0f);
	CachedMoveInputIntent.Z = FMath::Clamp(MovementVector.Z, -1.0f, 1.0f);

	// if not using Mover, use the CMC
	if(!bUseMover )
	{
		// input is a Vector2D
	//	FVector2D MovementVector = Value.Get<FVector2D>();

		ACharacter* OwnerCharacter = Cast<ACharacter>( GetOwner() );

		if( OwnerCharacter == nullptr )
		{
			UE_LOG( LogTemp , Error , TEXT( "'%s' Owner is not a Character!" ) , *GetNameSafe( this ) );
			return;
		}

		if (OwnerCharacter->Controller != nullptr)
		{
			// find out which way is forward
			const FRotator Rotation = OwnerCharacter->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			OwnerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
			OwnerCharacter->AddMovementInput(RightDirection, MovementVector.X);
		}

	}
}

void UGxMoverInputProducerComponent::OnMoveCompleted(const FInputActionValue& Value)
{
	CachedMoveInputIntent = FVector::ZeroVector;
}

void UGxMoverInputProducerComponent::OnLookTriggered(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	CachedLookInput.Yaw = CachedTurnInput.Yaw = FMath::Clamp(LookVector.X, -1.0f, 1.0f);
	CachedLookInput.Pitch = CachedTurnInput.Pitch = FMath::Clamp(LookVector.Y, -1.0f, 1.0f);
}

void UGxMoverInputProducerComponent::OnLookCompleted(const FInputActionValue& Value)
{
	CachedLookInput = FRotator::ZeroRotator;
	CachedTurnInput = FRotator::ZeroRotator;
}

void UGxMoverInputProducerComponent::OnJumpStarted(const FInputActionValue& Value)
{
	bIsJumpJustPressed = !bIsJumpPressed;
	bIsJumpPressed = true;
}

void UGxMoverInputProducerComponent::OnJumpReleased(const FInputActionValue& Value)
{
	bIsJumpPressed = false;
	bIsJumpJustPressed = false;
}

void UGxMoverInputProducerComponent::OnFlyTriggered(const FInputActionValue& Value)
{
	bShouldToggleFlying = true;
}



void UGxMoverInputProducerComponent::ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult)
{
	OnProduceInput((float)SimTimeMs, InputCmdResult);




}



void UGxMoverInputProducerComponent::OnProduceInput( float DeltaMs , FMoverInputCmdContext& InputCmdResult )
{
	// Default implementation does nothing. Override in derived classes to produce input.
	FCharacterDefaultInputs& CharacterInputs = InputCmdResult.InputCollection.FindOrAddMutableDataByType<FCharacterDefaultInputs>();

	CharacterInputs.ControlRotation = FRotator::ZeroRotator;
	APawn* OwnerPawn	=	Cast<APawn>( GetOwner());

	if (APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController()))
	{
		CharacterInputs.ControlRotation = PC->GetControlRotation();
	}
	if (USpringArmComponent* SpringComp = OwnerPawn->FindComponentByClass<USpringArmComponent>())
	{
		// This is not best practice: do not search for component every frame
		SpringComp->bUsePawnControlRotation = true;
	}


	ProduceMoveInput( DeltaMs , CharacterInputs );

	CharacterInputs.bIsJumpPressed = bIsJumpPressed;
	CharacterInputs.bIsJumpJustPressed = bIsJumpJustPressed;

	// Clear/consume temporal movement inputs. We are not consuming others in the event that the game world is ticking at a lower rate than the Mover simulation. 
	// In that case, we want most input to carry over between simulation frames.
	{

		bIsJumpJustPressed = false;
		bShouldToggleFlying = false;
	}

}


void UGxMoverInputProducerComponent::ProduceMoveInput( float DeltaMs , FCharacterDefaultInputs& CharacterInputs )
{
	// Favor velocity input 
	bool bUsingInputIntentForMove = CachedMoveInputVelocity.IsZero();

	if (bUsingInputIntentForMove)
	{
		const FVector FinalDirectionalIntent = CharacterInputs.ControlRotation.RotateVector(CachedMoveInputIntent);
		CharacterInputs.SetMoveInput(EMoveInputType::DirectionalIntent, FinalDirectionalIntent);
	}
	else
	{
		CharacterInputs.SetMoveInput(EMoveInputType::Velocity, CachedMoveInputVelocity);
	}

	static float RotationMagMin(1e-3);
	const bool bHasAffirmativeMoveInput = (CharacterInputs.GetMoveInput().Size() >= RotationMagMin);
	
	// Figure out intended orientation
	CharacterInputs.OrientationIntent = FVector::ZeroVector;

	if (bHasAffirmativeMoveInput)
	{
		if (bOrientRotationToMovement)
		{
			// set the intent to the actors movement direction
			CharacterInputs.OrientationIntent = CharacterInputs.GetMoveInput().GetSafeNormal();
		}
		else
		{
			// set intent to the the control rotation - often a player's camera rotation
			CharacterInputs.OrientationIntent = CharacterInputs.ControlRotation.Vector().GetSafeNormal();
		}

		LastAffirmativeMoveInput = CharacterInputs.GetMoveInput();
	}
	else if (bMaintainLastInputOrientation)
	{
		// There is no movement intent, so use the last-known affirmative move input
		CharacterInputs.OrientationIntent = LastAffirmativeMoveInput;
	}

}
