// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatioalPhysics.h"
#include "EngineUtils.h"

#include "Shower.h"

// Sets default values
AShower::AShower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShower::BeginPlay()
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
	
	// This is 'this' actor, could be a Blueprint child
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (!Comp) continue;

		// Log the name of each component
		UE_LOG(LogTemp, Log, TEXT("Component: %s"), *Comp->GetName());

		// Example: check if it's a Niagara component
		if (UNiagaraComponent* NiagaraComp = Cast<UNiagaraComponent>(Comp))
		{
			UE_LOG(LogTemp, Log, TEXT("Found Niagara Component: %s"), *NiagaraComp->GetName());

			WaterComponent = NiagaraComp;
		}
	}

}

// Called every frame
void AShower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TorusSystem)
	{
		FVector Gravity = TorusSystem->GetGravityAtLocation(GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("Gravity at location: X=%.2f Y=%.2f Z=%.2f"), Gravity.X, Gravity.Y, Gravity.Z);
		
		if (WaterComponent)
		{
			UE_LOG(LogTemp, Log, TEXT("HERE"));
			WaterComponent->SetVectorParameter(FName("User.Gravity"), Gravity);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Not HERE"));
		}
	}


}

