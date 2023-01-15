// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "NiagaraComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "VRPawn.generated.h"

	
UCLASS()
class HONOURSPROJECT_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* SceneComponent;
	UPROPERTY(BlueprintReadWrite)
	UMotionControllerComponent* MotionControllerRight;
	UPROPERTY(BlueprintReadWrite)
	UMotionControllerComponent* MotionControllerLeft;
	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* CameraComponent;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* HMD;
	UPROPERTY(BlueprintReadWrite)
	UNiagaraComponent* TeleportTraceNiagaraSystem;
	UPROPERTY(BlueprintReadWrite)
	UMotionControllerComponent* MotionControllerRightAim;
	UPROPERTY(BlueprintReadWrite)
	UWidgetInteractionComponent* WidgetInteractionRight;
	UPROPERTY(BlueprintReadWrite)
	UMotionControllerComponent* MotionControllerLeftAim;
	UPROPERTY(BlueprintReadWrite)
	UWidgetInteractionComponent* WidgetInteractionLeft;



	FVector ProjectedTeleportLocation;

	bool bValidTeleportLocation;

	bool bTeleportTraceActive;

	float GrabRadiusFromGripPosition;

	float AxisDeadzoneThreshold;

	class AVRTeleportVisualizer* TeleportVisualizerReference;

	float SnapTurnDegrees;

	TArray<FVector> TeleportTracePathPositions;

	FVector TeleportProjectPointToNavigationQueryExtent;

	class AMenu* MenuReference;

	bool bCanDoSnapTurn = false;

	class UGrabComponent* HeldComponentLeft;
	
	class UGrabComponent* HeldComponentRight;

	
	
	void StartTeleportTrace();

	void TeleportTrace(FVector StartPos,FVector ForwardVector);

	bool IsValidTeleportLocation(FHitResult InHit, FVector &OutProjectedLocation);

	void EndTeleportTrace();

	void TryTeleport();

	class UGrabComponent* GetGrabComponentNearMotionController(UMotionControllerComponent* MotionController);

	bool IsAxisGreaterThanDeadzone(float AxisValue);

	void LeftMenu();

	void RightMenu();
	
	void ToggleMenu(bool bActiveMenuHandRight);

	void DetermineSnapTurn(float AxisValue);

	void SnapTurn(bool bRightTurn);

	void DetermineTeleport(float AxisValue);

	void StartLeftGrab();

	void ReleaseLeftGrab();

	void StartRightGrab();

	void ReleaseRightGrab();

	void TriggerLeft();

	void TriggerReleasedLeft();

	void TriggerRight();

	void TriggerReleasedRight();

	void TriggerLeftAxis(float AxisValue);

	void TriggerRightAxis(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
