// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicDamageCalculate.h"
#include "BaseCharacterStatus.h"

struct DamageStatics 
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(_attackPoint)

	DECLARE_ATTRIBUTE_CAPTUREDEF(_defencePoint)
	DECLARE_ATTRIBUTE_CAPTUREDEF(_health)

	DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseCharacterStatus, _attackPoint, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseCharacterStatus, _defencePoint, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseCharacterStatus, _health, Target, false);
	}
};

static const DamageStatics& DStatics()
{
	static DamageStatics DStatics;
	return DStatics;
}

UBasicDamageCalculate::UBasicDamageCalculate()
{
	RelevantAttributesToCapture.Add(DStatics()._attackPointDef);
	RelevantAttributesToCapture.Add(DStatics()._healthDef);
	RelevantAttributesToCapture.Add(DStatics()._defencePointDef);
}

void UBasicDamageCalculate::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* sourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* targetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* sourceActor = sourceASC ? sourceASC->GetOwnerActor() : nullptr;
	AActor* targetActor = targetASC ? targetASC->GetOwnerActor() : nullptr;

	auto spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* sourceTag = spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTag = spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParam;
	evaluationParam.SourceTags = sourceTag;
	evaluationParam.TargetTags = targetTag;

	float dp = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DStatics()._defencePointDef, evaluationParam, dp);

	float ap = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DStatics()._attackPointDef, evaluationParam, ap);

	float damageRate = spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Attack.DamageRate")), false, 1.f);

	float calculateDamage = (ap - dp) * damageRate;

	UE_LOG(LogTemp, Error, TEXT("공격 받았습니다. 최종 대미지 %f"), calculateDamage);

	if (0 < calculateDamage)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DStatics()._healthProperty, EGameplayModOp::Additive, -calculateDamage));
	}
}
