// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARProjPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARPROJECT_API AARProjPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void OnPossess(APawn* InPawn) override;
};
