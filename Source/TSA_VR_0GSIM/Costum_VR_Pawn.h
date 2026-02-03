// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MotionControllerComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Costum_VR_Pawn.generated.h"

UCLASS()
class TSA_VR_0GSIM_API ACostum_VR_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACostum_VR_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector CalculateVelocity(FVector LastPosition, FVector CurrentPosition);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UMotionControllerComponent *MotionControllerL;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UMotionControllerComponent *MotionControllerR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UStaticMeshComponent* RHandHandel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UStaticMeshComponent* LHandHandel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	USkeletalMesh* RHandMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	USkeletalMesh* LHandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	FVector RHandVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	FVector LHandVelocity;

	FVector RHandLastPosition;
	FVector LHandLastPosition;

	FVector RHandCurrentPosition;
	FVector LHandCurrentPosition;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
