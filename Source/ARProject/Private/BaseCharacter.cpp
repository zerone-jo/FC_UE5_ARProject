// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseCharacterStatus.h"
#include "BCAbilitySystemComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_asc = CreateAbstractDefaultSubobject<UBCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	_status = CreateDefaultSubobject<UBaseCharacterStatus>(TEXT("BaseStatus"));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return _asc;
}

UBaseCharacterStatus* ABaseCharacter::GetStatus() const
{
	return _status;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeStatus();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::InitializeStatus()
{
	if (nullptr == _asc)
	{
		return;
	}

	if (nullptr == _defaultStatusEffect)
	{
		UE_LOG(LogTemp, Error, TEXT("(%s)캐릭터의 기본 스테이터스 이펙트가 존재 하지 않습니다."), *GetName());

		return;
	}

	auto context = _asc->MakeEffectContext();
	context.AddSourceObject(this);
	auto handle = _asc->MakeOutgoingSpec(_defaultStatusEffect, 0, context);
	if (handle.IsValid())
	{
		_asc->ApplyGameplayEffectSpecToTarget(*handle.Data.Get(), _asc);
	}

	GiveDefaultAbilities();
}

void ABaseCharacter::GiveDefaultAbilities()
{
	if (nullptr == _asc)
	{
		return;
	}

	for (auto& ability : _defaultAbilities)
	{
		_asc->GiveAbility(FGameplayAbilitySpec(ability, 0, 0, this));
	}
}

void ABaseCharacter::TryActiveAbility(int32 id)
{
	auto spec = _asc->FindAbilitySpecFromInputID(id);
	if (nullptr == spec)
	{
		return;
	}

	_asc->TryActivateAbility(spec->Handle);
}

