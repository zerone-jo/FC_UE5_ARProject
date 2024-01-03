// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseCharacterStatus.h"
#include "BCAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../ARProject.h"

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

void ABaseCharacter::UpdateTrajectory(FVector startPos, FVector endPos, float arc, USplineComponent* spline, UStaticMesh* pMesh)
{
	ClearTrajectory();

	if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, _projectileVelocity, startPos, endPos, GetWorld()->GetGravityZ(), arc))
	{
		FPredictProjectilePathParams param(5.f, startPos, _projectileVelocity, 5.f);
		FPredictProjectilePathResult result;
		UGameplayStatics::PredictProjectilePath(this, param, result);

		{
			auto len = result.PathData.Num();
			for (int ii = 0; ii < len; ++ii)
			{
				spline->AddSplinePointAtIndex(result.PathData[ii].Location, ii, ESplineCoordinateSpace::World);
			}

			_currentSpline = spline;
		}

		{
			auto len = spline->GetNumberOfSplinePoints();
			for (int ii = 0; ii < len; ++ii)
			{
				USplineMeshComponent* splineMesh = NewObject< USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
				splineMesh->SetForwardAxis(ESplineMeshAxis::Z);
				splineMesh->SetStaticMesh(pMesh);
				splineMesh->SetMobility(EComponentMobility::Movable);
				splineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
				splineMesh->RegisterComponentWithWorld(GetWorld());
				splineMesh->AttachToComponent(spline, FAttachmentTransformRules::KeepRelativeTransform);
				
				const FVector& start = spline->GetLocationAtSplinePoint(ii, ESplineCoordinateSpace::Local);
				const FVector& startTangent = spline->GetTangentAtSplinePoint(ii, ESplineCoordinateSpace::Local);
				const FVector& end = spline->GetLocationAtSplinePoint(ii + 1, ESplineCoordinateSpace::Local);
				const FVector& endTangent = spline->GetTangentAtSplinePoint(ii +1, ESplineCoordinateSpace::Local);

				splineMesh->SetStartAndEnd(start, startTangent, end, endTangent, true);
				splineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				_splineMeshs.Add(splineMesh);
			}
		}
	}
}

void ABaseCharacter::ClearTrajectory()
{
	{
		if (_currentSpline)
		{
			_currentSpline->ClearSplinePoints(true);
		}
		auto len = _splineMeshs.Num();

		for (int ii = 0; ii < len; ++ii)
		{
			if (_splineMeshs[ii])
			{
				_splineMeshs[ii]->DestroyComponent();
			}
		}

		_splineMeshs.Empty();
	}
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

	BindASCInput();
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

void ABaseCharacter::BindASCInput()
{
	if (false == _isBoundInput && GetAbilitySystemComponent() && IsValid(InputComponent))
	{
		FTopLevelAssetPath enumPath = FTopLevelAssetPath(FName("/Script/ARProject"), FName("ARProjAbilityID"));
		GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget")
			, enumPath, static_cast<int32>(ARProjAbilityID::ConfirmTarget), static_cast<int32>(ARProjAbilityID::CancelTarget)));

		_isBoundInput = true;
	}
}

