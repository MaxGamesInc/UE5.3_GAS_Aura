// Copyright MaxGamesInc


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"




AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;

}
void AAuraPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    CursorTrace();

}
void AAuraPlayerController::CursorTrace()
{
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
    if(!CursorHit.bBlockingHit) return;
    LastActor = ThisActor;
    ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
    
    /*
    *Line Trace from cursor . There are several scenarios:
        A.LastActor is null && ThisActor is null (Nothing was traced , Nothing is being traced)
        -> Do Nothing 
        B. LastActor is null && ThisActor is valid (Nothing was traced , Something is being traced)
        -> Highlight ThisActor
        C. LastActor is valid && ThisActor is null (Something was traced ,Nothing is being traced)
        -> UnHighlight LastActor
        D. Both Actors are Valid , but Last Actor != This Actor (Something was Traced , Something is being traced , but Something was traced and Something being traced is not same Actor)
        -> UnHighlight LastActor, Highlight ThisActor
        E. Both Actors are Valid , but Last Actor == This Actor (Something was Traced , Something is being traced , and both actors are same)
        -> Do Nothing
    */
   if (ThisActor != LastActor)
   {
    // Covers case A,B,C, and E
        if(LastActor != nullptr)
        {
            // Case C
            LastActor->UnHighlightActor();
            
        }
        if(ThisActor != nullptr)
        {
            // Case B
            ThisActor->HighlightActor();
        }
        // Case A and E has Nothing to Do , so no if checks.
   }


}

void AAuraPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    check(AuraContext); 
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);
    Subsystem->AddMappingContext(AuraContext,0);
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
}
void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    UEnhancedInputComponent* EnhancedInputComponent =CastChecked<UEnhancedInputComponent>(InputComponent);
    EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
    EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Look);
}
void AAuraPlayerController::Move(const FInputActionValue &InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    
    if(APawn* ControlledPawn =GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
    }

}
void AAuraPlayerController::Look(const FInputActionValue & InputActionValue)
{
const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
	
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
 
	}
}

