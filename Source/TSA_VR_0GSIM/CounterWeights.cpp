// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TorusSystem.h"
#include "RotatioalPhysics.h"
#include "EngineUtils.h"
#include "CounterWeights.h"


/////////////////////////////////////////////////
//////this is no simulated properly but it is ///
//////emulated to portray the idea of ///////////
//////a counter weight system controlling speed//
/////////////////////////////////////////////////
// Sets default values
ACounterWeights::ACounterWeights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACounterWeights::BeginPlay()
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

	
	// This is 'this' actor, could be a Blueprint child
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (!Comp) continue;

		// Log the name of each component
		UE_LOG(LogTemp, Log, TEXT("Component: %s"), *Comp->GetName());

		// Example: check if it's a Niagara component
		if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Comp))
		{
			UE_LOG(LogTemp, Log, TEXT("Found Mesh Component on counter weight: %s"), *MeshComp->GetName());

			MainMesh = MeshComp;
		}
	}

	
}

// Called every frame
void ACounterWeights::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetAngle(TorusSystem->GetAngularVelocity());

}

void ACounterWeights::SetAngle(float AngularVelocity)
{

	float MultipleOfNintey = AngularVelocity / (0.718 * 5); // over 5 g's of rotation

	FRotator CurrentRotation = this->GetActorRotation();

	float angle = (90 * MultipleOfNintey);

	FRotator BaseRotation = (FRotator(0.0f, 90 - angle, -90.0f));

	if (this->GetActorLocation().X > 0)
	{
		//nothing needed here
	}
	if (this->GetActorLocation().X < 0)
	{
		BaseRotation += FRotator(0.0f, 180.0f, 0.0f);
	}
	if (this->GetActorLocation().Y > 0)
	{
		BaseRotation += FRotator(0.0f, 90.0f, 0.0f);
	}
	if (this->GetActorLocation().Y < 0)
	{
		BaseRotation += FRotator(0.0f, -90.0f, 0.0f);
	}

	//this->SetActorRotation(FRotator(0.0f, angle, -90.0f));
	this->SetActorRotation(BaseRotation);
}

