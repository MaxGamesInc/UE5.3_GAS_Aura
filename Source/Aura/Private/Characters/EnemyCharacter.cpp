// Copyright MaxGamesInc


#include "Characters/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
  GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

}
void AEnemyCharacter::UnHighlightActor()
{
  bHighlighted  = false;
  GetMesh()->SetRenderCustomDepth(false);
  WeaponMesh->SetRenderCustomDepth(false);

} 


void AEnemyCharacter::HighlightActor()
{ 
  bHighlighted  = true;
  GetMesh()->SetRenderCustomDepth(true);
  GetMesh()->SetCustomDepthStencilValue(250.f);
  WeaponMesh->SetRenderCustomDepth(true);
  WeaponMesh->SetCustomDepthStencilValue(250.f);

}

