// Fill out your copyright notice in the Description page of Project Settings.


#include "Costum_VR_Pawn.h"

// Sets default values
ACostum_VR_Pawn::ACostum_VR_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACostum_VR_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACostum_VR_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACostum_VR_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

