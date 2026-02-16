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

	MainActor = GetOwner();

	// This is 'this' actor, could be a Blueprint child
	TArray<UActorComponent*> Components;
	MainActor->GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (!Comp) continue;

		// Log the name of each component
		UE_LOG(LogTemp, Log, TEXT("Component: %s"), *Comp->GetName());

		// Example: check if it's a Mesh component
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Comp))
		{
			UE_LOG(LogTemp, Log, TEXT("Found Mesh Component: %s"), *MeshComp->GetName());

			MainMesh = MeshComp;
		}
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
	

	FVector Location = MainActor->GetActorLocation();

	// angle = than^-1 of y/x
	// we dont care about the third dimension
	float Angle = atan(Location.Y / Location.X);
	UE_LOG(LogTemp, Log, TEXT("Angle is %f"), Angle);
	FVector Gravity(0,0,0);

	float DeltaAngle;

	if (LastAngleOfActor)
	{
		DeltaAngle = LastAngleOfActor - Angle;
		Gravity = TorusSystem->GetGravityAtLocationMoving(Location, DeltaAngle / DeltaTime);
		LastAngleOfActor = Angle;
	}
	else
	{
		Gravity = TorusSystem->GetGravityAtLocation(Location);
	}

	UE_LOG(LogTemp, Warning, TEXT("Location: X=%f Y=%f Z=%f"), Location.X, Location.Y, Location.Z);
	UE_LOG(LogTemp, Warning, TEXT("Gravity: X=%f Y=%f Z=%f"), Gravity.X, Gravity.Y, Gravity.Z);

	GravityActing = Gravity;
	GravMag = sqrt((Gravity.X * Gravity.X) + (Gravity.Y * Gravity.Y) + (Gravity.Z * Gravity.Z));

	MainMesh->AddForce(Gravity);
}
