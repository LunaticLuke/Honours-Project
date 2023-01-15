// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumManager.h"
#include "Components/SceneComponent.h"
#include "GrabComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONOURSPROJECT_API UGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabComponent();

	bool TryGrab(class UMotionControllerComponent* MotionController);

	bool TryRelease();

	void TriggerPressed();

	void TriggerReleased();

	void TriggerAxis(float AxisValue);

	void SetShouldSimulateOnDrop();

	void SetPrimitiveCompPhysics(bool Simulate);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	EGrabType GrabType = EGrabType::Free;

	bool bIsHeld;

	FRotator PrimaryGrabRelativeRotation;

	bool bSimulateOnDrop;

	UHapticFeedbackEffect_Base* OnGrabHapticEffect;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
