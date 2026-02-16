// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorusSystem.h"
#include "EngineUtils.h" 
#include "AngularVelocityController.generated.h"

UCLASS()
class TSA_VR_0GSIM_API AAngularVelocityController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAngularVelocityController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATorusSystem *TorusSystem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AngularVelocity = 0.718;
};
