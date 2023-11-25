// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacterStatus.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ARPROJECT_API UBaseCharacterStatus : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& newValue) override;
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    FGameplayAttributeData _health;
    ATTRIBUTE_ACCESSORS(UBaseCharacterStatus, _health)

    FGameplayAttributeData _maxHealth;
    ATTRIBUTE_ACCESSORS(UBaseCharacterStatus, _maxHealth)

    FGameplayAttributeData _stamina;
    ATTRIBUTE_ACCESSORS(UBaseCharacterStatus, _stamina)

    FGameplayAttributeData _maxStamina;
    ATTRIBUTE_ACCESSORS(UBaseCharacterStatus, _maxStamina)
};
