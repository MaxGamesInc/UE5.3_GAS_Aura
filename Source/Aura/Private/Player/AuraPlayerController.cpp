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
    

   if (ThisActor != LastActor)
   {
        if(LastActor != nullptr)
        {
  
            LastActor->UnHighlightActor();
            
        }
        if(ThisActor != nullptr)
        {
  
            ThisActor->HighlightActor();
        }

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
    EnhancedInputComponent->BindAction(ToggleCombatModeAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::ToggleCombatMode);
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
void AAuraPlayerController::Look(const FInputActionValue &InputActionValue)
{
const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
	
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
 
	}
}

void AAuraPlayerController::ToggleCombatMode(const FInputActionValue &InputActionValue)
{
    const bool CombatModeToggle = InputActionValue.Get<bool>();
   
}

