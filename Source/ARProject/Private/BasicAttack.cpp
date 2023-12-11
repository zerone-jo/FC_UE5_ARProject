// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicAttack.h"
#include "BaseCharacter.h"
#include "AbilitySystemComponent.h"

void UBasicAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	auto source = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());
	if (!source)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	auto asc = source->GetAbilitySystemComponent();

	auto effectContext = asc->MakeEffectContext();
	effectContext.AddSourceObject(source);

	auto damageSpec = MakeOutgoingGameplayEffectSpec(_damageEffect, GetAbilityLevel());
	damageSpec.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Attack.DamageRate")), _damageRate);

	asc->ApplyGameplayEffectSpecToTarget(*damageSpec.Data.Get(), asc);
}
