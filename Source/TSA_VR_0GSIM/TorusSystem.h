// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorusSystem.generated.h"

UCLASS()
class TSA_VR_0GSIM_API ATorusSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorusSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity Field")
    UStaticMeshComponent* GravField;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity Field")
    UStaticMeshComponent* Hull;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity Field Physics")
	TArray<AActor*> ActorsInField;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity Field Physics")
	TArray<FVector> ActorsDistanceFromCenter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> GetActorsInField();
	TArray<FVector> GetDistances();

};
