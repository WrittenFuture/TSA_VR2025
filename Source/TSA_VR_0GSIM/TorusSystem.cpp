// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"
#include "TorusSystem.h"

// Sets default values
ATorusSystem::ATorusSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATorusSystem::BeginPlay()
{
	Super::BeginPlay();

	Hull = Cast<UStaticMeshComponent>(GetRootComponent());

	if (Hull)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hull Name: %s"), *Hull->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hull Failed"));
		return;
	}

	TArray<USceneComponent *> ChildrenOfComponent;
	GetRootComponent()->GetChildrenComponents(true, ChildrenOfComponent);

	if (ChildrenOfComponent.Num() > 0)
	{
		GravField = Cast<UStaticMeshComponent>(ChildrenOfComponent[0]);
	}

	if (GravField)
	{
		UE_LOG(LogTemp, Warning, TEXT("GravField Name: %s"), *GravField->GetName());
		GravField->SetGenerateOverlapEvents(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GravField Failed"));
		return;
	}

	GravField->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GravField->SetCollisionObjectType(ECC_WorldDynamic);
	GravField->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// Overlap with what you care about:
	GravField->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GravField->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	GravField->SetGenerateOverlapEvents(true);

	UE_LOG(LogTemp, Warning, TEXT("GravField overlap? %s, collision: %d"),
		   GravField->GetGenerateOverlapEvents() ? TEXT("true") : TEXT("false"),
		   (int32)GravField->GetCollisionEnabled());

	SetAngularVelocity(0.718);
}

// Called every frame
void ATorusSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Hull == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NO HULL"))
		return;
	}

	if (GravField == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NO FIELD"))
		return;
	}

	TArray<AActor *> OverlappingActors;
	GravField->GetOverlappingActors(OverlappingActors);

	//UE_LOG(LogTemp, Warning, TEXT("Overlapping count: %d"), OverlappingActors.Num());

	for (AActor *Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside mesh: %s"), *Actor->GetName());
	}

	ActorsInField = OverlappingActors;

	if (PhysicsItterator % 15 == 0)
	{
		int Itterator = 0;

		for (AActor *Actor : GetActorsInField())
		{
			UStaticMeshComponent *Mesh = Cast<UStaticMeshComponent>(Actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

			if (Mesh && Mesh->IsSimulatingPhysics())
			{
				//Mesh->AddForce(CalcVector(Itterator));
				UE_LOG(LogTemp, Warning, TEXT("Added force *or would have TorusSystem.cpp line 104 commebnted out*"))
			}
			UE_LOG(LogTemp, Warning, TEXT("Cycled one ActorInField"))
			Itterator++;
		}
	}

	PhysicsItterator++;
}

TArray<AActor *> ATorusSystem::GetActorsInField()
{
	return ActorsInField;
}

TArray<FVector> ATorusSystem::GetDistances()
{
	for (AActor *Actor : GetActorsInField())
	{
		FVector Distance = Actor->GetActorLocation() - Hull->GetComponentLocation();

		ActorsDistanceFromCenter.Add(Distance);
	}

	return ActorsDistanceFromCenter;
}

float ATorusSystem::GetAngularVelocity()
{
	return AngularVelocity;
}

TArray<FRotator> ATorusSystem::GetOrientation()
{
	TArray<FRotator> Orientations;
    
    TArray<FVector> Distances = GetDistances();

    for (FVector Position : Distances)
    {
        FRotator Rot = Position.GetSafeNormal().Rotation(); // vector from center to actor -> rotation
        Orientations.Add(Rot);
    }

    return Orientations;
}

void ATorusSystem::SetAngularVelocity(float NewAVelocity)
{	
	AngularVelocity = NewAVelocity;
}

FVector ATorusSystem::CalcVector(int Index)
{
	return GetDistances()[Index] * 9.8;
}


FVector ATorusSystem::GetGravityAtLocation(FVector Location)
{
	float AngularSquared = AngularVelocity * AngularVelocity;
	UE_LOG(LogTemp, Log, TEXT("Angular Velocity: %.2f"), AngularVelocity);

	FVector Gravity = FVector(
		AngularSquared * Location.X,
		AngularSquared * Location.Y,
		AngularSquared * Location.Z
	);

	return Gravity;
	
}

FVector ATorusSystem::GetGravityAtLocationMoving(FVector Location, float AdditionAngularVelocity)
{
	float TotalAngularVelocity = AngularVelocity + AdditionAngularVelocity;
	float AngularSquared = TotalAngularVelocity * TotalAngularVelocity;
	UE_LOG(LogTemp, Log, TEXT("Angular Velocity: %.2f"), AngularVelocity);

	FVector Gravity = FVector(
		AngularSquared * Location.X,
		AngularSquared * Location.Y,
		AngularSquared * Location.Z
	);

	return Gravity;
	
}