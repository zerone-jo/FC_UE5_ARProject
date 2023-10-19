// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FSM.generated.h"

UENUM(BlueprintType)
enum class AIState : uint8
{
	AIState_Idle UMETA(DisplayName = "Idle"),
	AIState_Patrol UMETA(DisplayName = "Patrol"),
	AIState_Chase UMETA(DisplayName = "Chase"),
	AIState_Attack UMETA(DisplayName = "Attack"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPROJECT_API UFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFSM();

	UPROPERTY(BlueprintReadOnly)
	AIState _currentState;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TWeakObjectPtr<AActor> _owner;
	TWeakObjectPtr<AActor> _target;

	FVector _currentDirection;
	FVector _destination;
	UPROPERTY(EditDefaultsOnly)
	float _speed;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FSM(float dt);

	void Idle(float dt);
	void Patrol(float dt);
	void Chase(float dt);
	void Attack(float dt);
};
