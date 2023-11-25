// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterStatus.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void UBaseCharacterStatus::PreAttributeChange(const FGameplayAttribute& Attribute, float& newValue)
{
	// NULL
}

void UBaseCharacterStatus::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == Get_healthAttribute())
	{
		Set_health(FMath::Clamp(Get_health(), 0.f, Get_maxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == Get_staminaAttribute())
	{
		Set_stamina(FMath::Clamp(Get_stamina(), 0.f, Get_maxStamina()));
	}
}
