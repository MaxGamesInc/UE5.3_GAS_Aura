// Copyright MaxGamesInc


#include "Characters/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


AURA_API AAuraCharacter::AAuraCharacter()
{
  
  GetCharacterMovement()->bOrientRotationToMovement = true;
  GetCharacterMovement()->bUseControllerDesiredRotation = false;
  GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
  GetCharacterMovement()->bConstrainToPlane = true;
  GetCharacterMovement()->bSnapToPlaneAtStart = true;
    bUseControllerRotationPitch = false; 
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;
}

