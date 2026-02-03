// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TorusSystem.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotatioalPhysics.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TSA_VR_0GSIM_API URotatioalPhysics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URotatioalPhysics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor *> ActorsToSimulate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATorusSystem *TorusSystem = nullptr;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
