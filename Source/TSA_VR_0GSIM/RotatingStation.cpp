// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingStation.h"
#include "PhysicsSubsystem.h"

// Sets default values
ARotatingStation::ARotatingStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotatingStation::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("RotatingStation BeginPlay"));

	UStaticMeshComponent* MeshComp = FindComponentByClass<UStaticMeshComponent>();

	UPhysicsSubsystem* PhysicsSubsystem = GetGameInstance()->GetSubsystem<UPhysicsSubsystem>();
	if (PhysicsSubsystem)
	{
		// Assuming you have a UStaticMeshComponent* named MeshComp and a float Force defined somewhere
		// PhysicsSubsystem->StartRotation(MeshComp, Force);
		PhysicsSubsystem->StartRotation(MeshComp, 750.0f); // Replace nullptr with your actual mesh component
	}
	
}

// Called every frame
void ARotatingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

