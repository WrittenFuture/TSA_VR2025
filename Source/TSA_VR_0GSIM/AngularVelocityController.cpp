// Fill out your copyright notice in the Description page of Project Settings.

#include "TorusSystem.h"
#include "EngineUtils.h" 

#include "AngularVelocityController.h"

// Sets default values
AAngularVelocityController::AAngularVelocityController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAngularVelocityController::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATorusSystem> It(GetWorld()); It; ++It)
	{
		TorusSystem = *It;
		break; // only one, so stop immediately
	}

	if (TorusSystem != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("TorusSystem assigned SHOWER"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Torus system null SHOWER"))
	}

	AngularVelocity = 0.718;
	
}

// Called every frame
void AAngularVelocityController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TorusSystem->SetAngularVelocity(AngularVelocity);
}

