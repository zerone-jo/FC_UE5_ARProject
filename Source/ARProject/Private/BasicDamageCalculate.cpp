// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicDamageCalculate.h"

void UBasicDamageCalculate::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto spec = ExecutionParams.GetOwningSpec();
	float damageRate = spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Attack.DamageRate")), false);

	UE_LOG(LogTemp, Error, TEXT("공격 받았습니다. 대미지배율 %f"), damageRate);
}
