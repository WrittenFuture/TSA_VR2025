// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CounterWeights.generated.h"

UCLASS()
class TSA_VR_0GSIM_API ACounterWeights : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACounterWeights();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATorusSystem *TorusSystem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor *MainActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebugAngle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void SetAngle(float AngularVelocity);
};
