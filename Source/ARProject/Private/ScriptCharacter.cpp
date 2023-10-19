// Fill out your copyright notice in the Description page of Project Settings.


#include "ScriptCharacter.h"

void AScriptCharacter::SampleFunc()
{
	//auto newObject = NewObject<AScriptCharacter>();
	//auto newObject = GetWorld()->SpawnActor<AScriptCharacter>(_samepleScriptCharacterClass.Get(), GetActorLocation() + GetActorForwardVector() * 2, GetActorRotation());

	DFunc.ExecuteIfBound();
	if (DynamicSample.IsBound())
	{
		DynamicSample.Execute(100);
	}

	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, TEXT("Call Sample Function!"));
}

void AScriptCharacter::OnlyScriptFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, TEXT("This Is Only Script Function!"));
}

// Sets default values
AScriptCharacter::AScriptCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScriptCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AScriptCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AScriptCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

