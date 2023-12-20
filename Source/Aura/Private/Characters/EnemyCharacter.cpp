// Copyright MaxGamesInc


#include "Characters/EnemyCharacter.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
  GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
  AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
  AbilitySystemComponent->SetIsReplicated(true);
  AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal );
  AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
  

}
void AEnemyCharacter::BeginPlay()
{
  Super::BeginPlay();
  AbilitySystemComponent->InitAbilityActorInfo(this,this );
  
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



