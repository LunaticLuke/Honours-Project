// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VRInteractionAPI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVRInteractionAPI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HONOURSPROJECT_API IVRInteractionAPI
{
	GENERATED_BODY()

public:
	
	virtual void TriggerAxis(float AxisValue) = 0;

	
	virtual void TriggerPressed() = 0;

	
	virtual void TriggerReleased() = 0;

	
	virtual void SecondaryTriggerAxis(float AxisValue) = 0;
	
	
	virtual void SecondaryTriggerPressed() = 0;


	virtual void SecondaryTriggerReleased() = 0;
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
