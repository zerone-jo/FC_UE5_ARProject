// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ARProjAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPROJECT_API UARProjAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
	virtual void StartInitialLoading() override;
};
