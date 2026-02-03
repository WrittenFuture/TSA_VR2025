// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"    // for TActorIterator

#include "RotatioalPhysics.h"

// Sets default values for this component's properties
URotatioalPhysics::URotatioalPhysics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URotatioalPhysics::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATorusSystem> It(GetWorld()); It; ++It)
	{
		TorusSystem = *It;
		break; // only one, so stop immediately
	}

	if (TorusSystem != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("TorusSystem assigned"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Torus system null"))
	}

}

// Called every frame
void URotatioalPhysics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (TorusSystem)
	{
		ActorsToSimulate = TorusSystem->GetActorsInField();

		for (AActor* Actor : TorusSystem->GetActorsInField())
		{
			//UE_LOG(LogTemp, Log, TEXT("Item in GETACTORSINSOEIJAOJDFLSKj"));
		}
		UE_LOG(LogTemp, Log, TEXT("Got ActorsInField"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to assign TorusSystem in aactor"));
	}

	for (AActor* Actor : ActorsToSimulate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hi yes me i am simulated"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("Failed to assign Actor"));
}
