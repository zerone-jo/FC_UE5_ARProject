// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ARPROJECT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	class UBaseCharacterStatus* GetStatus() const;

protected:
	UPROPERTY()
	class UAbilitySystemComponent* _asc;
	UPROPERTY()
	class UBaseCharacterStatus* _status;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem|Status")
	TSubclassOf<class UGameplayEffect> _defaultStatusEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem|Ability")
	TArray < TSubclassOf<class UGameplayAbility>> _defaultAbilities;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitializeStatus();
	void GiveDefaultAbilities();

	UFUNCTION(Blueprintcallable)
	void TryActiveAbility(int32 id);
};
