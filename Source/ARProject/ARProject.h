// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ARProjAbilityID
{
	None			UMETA(DisplayName = "None"),
	ConfirmTarget	UMETA(DisplayName = "ConfirmTarget"),
	CancelTarget	UMETA(DisplayName = "CancelTarget"),
};