// Copyright MaxGamesInc


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"






UAuraAttributeSet::UAuraAttributeSet()
{
    InitHealth(100.f);
    InitMaxHealth(100.f);
    InitMagic(250.f);
    InitMaxMagic(250.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
     Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Magic,COND_None,REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMagic,COND_None,REPNOTIFY_Always);
}
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}
void UAuraAttributeSet::OnRep_Magic(const FGameplayAttributeData OldMagic) const
{
   GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Magic,OldMagic);  
}

void UAuraAttributeSet::OnRep_MaxMagic(const FGameplayAttributeData OldMaxMagic) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMagic,OldMaxMagic);
}
