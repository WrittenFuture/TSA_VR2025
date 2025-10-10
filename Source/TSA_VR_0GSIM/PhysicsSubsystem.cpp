// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsSubsystem.h"

void UPhysicsSubsystem::StartRotation(UStaticMeshComponent* MeshComp, float Force)
{

    UE_LOG(LogTemp, Warning, TEXT("PhysicsSubsystem StartRotation called"));

    if (MeshComp)
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetEnableGravity(false);
        MeshComp->SetAngularDamping(0.0f);
        MeshComp->AddTorqueInRadians(FVector(0.0f, 0.0f, Force), NAME_None, true);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("MeshComp is null in StartRotation"));
        return;
    }
}