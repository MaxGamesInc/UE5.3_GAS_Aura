// Copyright MaxGamesInc

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

class FLifeTimeProperty;
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Magic(const FGameplayAttributeData OldMagic) const;
	UFUNCTION()
	void OnRep_MaxMagic(const FGameplayAttributeData OldMaxMagic) const;


	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth,Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Magic,Category = "Vital Attributes")
	FGameplayAttributeData Magic;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Magic)
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMagic,Category = "Vital Attributes")
	FGameplayAttributeData MaxMagic;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMagic)
};
