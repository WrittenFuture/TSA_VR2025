// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationalGravityField.generated.h"

UCLASS()
class TSA_VR_0GSIM_API ARotationalGravityField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotationalGravityField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity Field")
    UStaticMeshComponent* GravField;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
