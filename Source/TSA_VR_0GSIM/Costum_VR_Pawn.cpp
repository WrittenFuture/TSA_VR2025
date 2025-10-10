// Fill out your copyright notice in the Description page of Project Settings.

#include "MotionControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Costum_VR_Pawn.h"

// Sets default values
ACostum_VR_Pawn::ACostum_VR_Pawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACostum_VR_Pawn::BeginPlay()
{
	Super::BeginPlay();

	TArray<UMotionControllerComponent *> Controllers;
	TArray<UStaticMeshComponent *> StaticMeshComponents;

	GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	GetComponents<UMotionControllerComponent>(Controllers);

	for (UMotionControllerComponent *MC : Controllers)
	{
		if (MC)
		{
			UE_LOG(LogTemp, Log, TEXT("Found MotionController: %s"), *MC->GetName());

			if (MC->GetName().Equals(TEXT("MotionControllerLeftGrip")))
			{
				MotionControllerL = MC;
				UE_LOG(LogTemp, Log, TEXT("Assigned Left MotionController"));
			}
			else if (MC->GetName().Equals(TEXT("MotionControllerRightGrip")))
			{
				MotionControllerR = MC;
				UE_LOG(LogTemp, Log, TEXT("Assigned Right MotionController"));
			}
		}
	}

	if (!StaticMeshComponents.IsEmpty())
	{
		for (UStaticMeshComponent *SMC : StaticMeshComponents)
		{
			if (SMC->GetName().Equals(TEXT("RightHandHandel")))
			{
				RHandHandel = SMC;
				RHandVelocity = RHandHandel->GetComponentVelocity();
				UE_LOG(LogTemp, Log, TEXT("Found Right_Handel"));
			}
			else if (SMC->GetName().Equals(TEXT("LeftHandHandel")))
			{
				LHandHandel = SMC;
				LHandVelocity = LHandHandel->GetComponentVelocity();
				UE_LOG(LogTemp, Log, TEXT("Found Left_Handel"));
			}
		}
	}
}

// Called every frame
void ACostum_VR_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LHandCurrentPosition = MotionControllerL->GetComponentLocation();

	LHandVelocity = CalculateVelocity(LHandLastPosition, LHandCurrentPosition);

	if (LHandVelocity.Size() > FVector(0,0,2).Size())
	{
		UE_LOG(LogTemp, Log, TEXT("Velocity L: %s"), *LHandVelocity.ToString());
	}
	
	LHandLastPosition = LHandCurrentPosition;
}

FVector ACostum_VR_Pawn::CalculateVelocity(FVector LastPosition, FVector CurrentPosition)
{
	if (LastPosition == FVector::ZeroVector || CurrentPosition == FVector::ZeroVector)
	{
		UE_LOG(LogTemp, Warning, TEXT("Last or Current Position is not set!"));
		return FVector::ZeroVector;
	}

	return (CurrentPosition - LastPosition); /// GetWorld()->GetDeltaSeconds();
}

// Called to bind functionality to input
void ACostum_VR_Pawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
