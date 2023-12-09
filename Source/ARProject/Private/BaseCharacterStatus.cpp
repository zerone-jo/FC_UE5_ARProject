// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterStatus.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void UBaseCharacterStatus::PreAttributeChange(const FGameplayAttribute& Attribute, float& newValue)
{
	Super::PreAttributeChange(Attribute, newValue);

	if (Attribute == Get_maxHealthAttribute())
	{
		AdjustChangeMaxStatus(_health, _maxHealth, newValue, Get_healthAttribute());
	}
	else if (Attribute == Get_maxStaminaAttribute())
	{
		AdjustChangeMaxStatus(_stamina, _maxStamina, newValue, Get_staminaAttribute());
	}
}

void UBaseCharacterStatus::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == Get_healthAttribute())
	{
		Set_health(FMath::Clamp(Get_health(), 0.f, Get_maxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == Get_staminaAttribute())
	{
		Set_stamina(FMath::Clamp(Get_stamina(), 0.f, Get_maxStamina()));
	}
}

void UBaseCharacterStatus::AdjustChangeMaxStatus(FGameplayAttributeData& affectAttribute, const FGameplayAttributeData& maxAttribute, float newValue, const FGameplayAttribute& affectAttributeProperty)
{
	auto asc = GetOwningAbilitySystemComponent();
	const float currentMax = maxAttribute.GetCurrentValue();
	if (false == FMath::IsNearlyEqual(currentMax, newValue) && asc)
	{
		const float current = affectAttribute.GetCurrentValue();
		float delta = (0 <= currentMax) ? (newValue - currentMax) : newValue;
		asc->ApplyModToAttributeUnsafe(affectAttributeProperty, EGameplayModOp::Additive, delta);
	}
}
