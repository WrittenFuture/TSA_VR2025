// Fill out your copyright notice in the Description page of Project Settings.

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

	UE_LOG(LogTemp, Warning, TEXT("Overlapping count: %d"), OverlappingActors.Num());

	for (AActor *Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside mesh: %s"), *Actor->GetName());
	}

	ActorsInField = OverlappingActors;
}

TArray<AActor*> ATorusSystem::GetActorsInField()
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