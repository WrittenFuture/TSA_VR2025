// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PhysicsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TSA_VR_0GSIM_API UPhysicsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	public:
		virtual void StartRotation(UStaticMeshComponent* MeshComp, float Force);
};
