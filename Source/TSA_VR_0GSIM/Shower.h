// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TorusSystem.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Shower.generated.h"

UCLASS()
class TSA_VR_0GSIM_API AShower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATorusSystem *TorusSystem = nullptr;

    // Reference to a Niagara system asset (water effect)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
    UNiagaraSystem* WaterEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Effects")
	UNiagaraComponent* WaterComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
