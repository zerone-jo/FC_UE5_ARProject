// Fill out your copyright notice in the Description page of Project Settings.


#include "ARProjAssetManager.h"
#include "AbilitySystemGlobals.h"

void UARProjAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
