// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "GrabComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "VRInteractionAPI.h"
#include "VRTeleportVisualizer.h"
#include "Kismet/GameplayStatics.h"
#include <NiagaraDataInterfaceArrayFunctionLibrary.h>

#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneComponent);

	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));
	MotionControllerRight->SetupAttachment(RootComponent);

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	MotionControllerLeft->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(RootComponent);

	HMD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD"));
	HMD->SetupAttachment(CameraComponent);

	TeleportTraceNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportTraceNiagaraSystem"));
	TeleportTraceNiagaraSystem->SetupAttachment(RootComponent);

	MotionControllerRightAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRightAim"));
	MotionControllerRightAim->SetupAttachment(RootComponent);

	WidgetInteractionRight = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionRight"));
	WidgetInteractionRight->SetupAttachment(MotionControllerRightAim);

	MotionControllerLeftAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeftAim"));
	MotionControllerLeftAim->SetupAttachment(RootComponent);

	WidgetInteractionLeft = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionLeft"));
	WidgetInteractionLeft->SetupAttachment(MotionControllerLeftAim);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if(UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),"vr.PixelDensity 1.0");
	}
	
}


// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MovementAxisLeft_X",this,&AVRPawn::DetermineSnapTurn);
	PlayerInputComponent->BindAxis("MovementAxisRight_Y",this,&AVRPawn::DetermineTeleport);
	
	PlayerInputComponent->BindAction("GrabLeft",IE_Pressed,this,&AVRPawn::StartLeftGrab);
	PlayerInputComponent->BindAction("GrabLeft",IE_Released,this,&AVRPawn::ReleaseLeftGrab);
	
	PlayerInputComponent->BindAction("GrabRight",IE_Pressed,this,&AVRPawn::StartRightGrab);
	PlayerInputComponent->BindAction("GrabRight",IE_Released,this,&AVRPawn::ReleaseRightGrab);
	
	PlayerInputComponent->BindAction("TriggerLeft",IE_Pressed,this,&AVRPawn::TriggerLeft);
	PlayerInputComponent->BindAction("TriggerLeft",IE_Released,this,&AVRPawn::TriggerReleasedLeft);
	
	PlayerInputComponent->BindAction("TriggerRight",IE_Pressed,this,&AVRPawn::TriggerRight);
	PlayerInputComponent->BindAction("TriggerRight",IE_Released,this,&AVRPawn::TriggerReleasedRight);

	PlayerInputComponent->BindAxis("TriggerAxisLeft",this,&AVRPawn::TriggerLeftAxis);
	PlayerInputComponent->BindAxis("TriggerAxisRight",this,&AVRPawn::TriggerRightAxis);

	PlayerInputComponent->BindAction("MenuToggleLeft",IE_Pressed,this,&AVRPawn::LeftMenu);
	PlayerInputComponent->BindAction("MenuToggleRight",IE_Pressed,this,&AVRPawn::RightMenu);
}

/**
 * @brief This function Begins The Process Of Teleporting By Spawning The Visualiser.
 */
void AVRPawn::StartTeleportTrace()
{
	//A teleport trace is now active
	bTeleportTraceActive = true;
	//Set particles to visible. 
	TeleportTraceNiagaraSystem->SetVisibility(true);
	//Spawn the visualiser At 0,0,0
	TeleportVisualizerReference = GetWorld()->SpawnActor<AVRTeleportVisualizer>();
}

/**
 * @brief This function carries out the trace of the teleport by predicting a projectile's motion - this gives an arc type trace.
 * @param StartPos The Position from which the projectile trace will be initiated
 * @param ForwardVector The direction in which the trace will be cast
 */
void AVRPawn::TeleportTrace(FVector StartPos, FVector ForwardVector)
{
	float LocalTeleportLaunchSpeed = 650; 
	float LocalTeleportProjectileRadius = 3.6; 
	float LocalNavMeshCellHeight = 8.0;
	
	
	FPredictProjectilePathParams PredParams;
	PredParams.StartLocation = StartPos;
	//The velocity is equal to being launched at the given speed in the direction of forward
	PredParams.LaunchVelocity = LocalTeleportLaunchSpeed * ForwardVector;
	PredParams.ProjectileRadius = LocalTeleportProjectileRadius;
	PredParams.ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	
	FPredictProjectilePathResult hit;

	//If the trace hits somewhere
	if(UGameplayStatics::PredictProjectilePath(GetWorld(),PredParams,hit))
	{
		TeleportTracePathPositions.Empty();
		TeleportTracePathPositions.Push(StartPos);
		for(int i = 0; i < hit.PathData.Num();i++)
		{
			TeleportTracePathPositions.Push(hit.PathData[i].Location);
		}
		FVector ProjectedLocation;
		bool bValidTeleport;
		bValidTeleport = IsValidTeleportLocation(hit.HitResult,ProjectedLocation);

		ProjectedTeleportLocation = FVector(ProjectedLocation.X,ProjectedLocation.Y,ProjectedLocation.Z - LocalNavMeshCellHeight);

		//Check to see if the global variable is updated with the most recent validity check
		if(bValidTeleportLocation != bValidTeleport)
		{
			//If not, update it.
			bValidTeleportLocation = bValidTeleport;
			//Set the visibility of the teleport particle to suit whether a valid teleport is available or not.
			TeleportVisualizerReference->GetRootComponent()->SetVisibility(bValidTeleportLocation,true);
		}
		
	}

	TeleportVisualizerReference->SetActorLocation(ProjectedTeleportLocation);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(TeleportTraceNiagaraSystem,FName("User.PointArray"),TeleportTracePathPositions);
	
}

bool AVRPawn::IsValidTeleportLocation(FHitResult InHit, FVector& OutProjectedLocation)
{
	//bool LocationFound;
	
	//auto NavSystem =UNavigationSystemV1::GetNavigationSystem(GetWorld());
	return false;
}

void AVRPawn::EndTeleportTrace()
{
}

void AVRPawn::TryTeleport()
{
}

UGrabComponent* AVRPawn::GetGrabComponentNearMotionController(UMotionControllerComponent* MotionController)
{
	return nullptr;
}

bool AVRPawn::IsAxisGreaterThanDeadzone(float AxisValue)
{
	return false;
}

void AVRPawn::LeftMenu()
{
	ToggleMenu(false);
}

void AVRPawn::RightMenu()
{
	ToggleMenu(true);
}

void AVRPawn::ToggleMenu(bool bActiveMenuRight)
{
}

void AVRPawn::DetermineSnapTurn(float AxisValue)
{
	if(IsAxisGreaterThanDeadzone(AxisValue))
	{
		bCanDoSnapTurn = true;
	}
	else
	{
		bCanDoSnapTurn = false;
	}

	if(bCanDoSnapTurn)
	{
		
		//Can Perform a snap turn, pass in whether the axis value is positive or negative to determine left or right.
		SnapTurn(AxisValue > 0.0f);
		bCanDoSnapTurn = false;
	}
}

void AVRPawn::SnapTurn(bool bRightTurn)
{
}

void AVRPawn::DetermineTeleport(float AxisValue)
{
	bool bCanTeleport = false;
	
	//Only interested in positive thumbstick movement...
	if(IsAxisGreaterThanDeadzone(AxisValue) && AxisValue > 0.0)
	{
		bCanTeleport = true;
		if(bCanTeleport)
		{
			StartTeleportTrace();
			bCanTeleport = false;
		}
		TeleportTrace(MotionControllerRightAim->GetComponentLocation(),MotionControllerRightAim->GetForwardVector());
	}
	else
	{
		if(bTeleportTraceActive)
		{
			EndTeleportTrace();
			TryTeleport();
			bCanTeleport = false;
		}
	}
	
}

void AVRPawn::StartLeftGrab()
{
	UGrabComponent* GrabbedComponent = GetGrabComponentNearMotionController(MotionControllerLeft);
	
	if (IsValid(GrabbedComponent))
	{
		if(GrabbedComponent->TryGrab(MotionControllerLeft))
		{
			HeldComponentLeft = GrabbedComponent;
			if(HeldComponentLeft == HeldComponentRight)
			{
				HeldComponentRight =  nullptr;
			}
		}
	}
	
}

void AVRPawn::ReleaseLeftGrab()
{
	if(HeldComponentLeft)
	{
		
		if(HeldComponentLeft->TryRelease())
		{
			HeldComponentLeft = nullptr;
		}
	}
}

void AVRPawn::StartRightGrab()
{
	UGrabComponent* GrabbedComponent = GetGrabComponentNearMotionController(MotionControllerRight);
	
	if (IsValid(GrabbedComponent))
	{
		if(GrabbedComponent->TryGrab(MotionControllerRight))
		{
			HeldComponentRight = GrabbedComponent;
			if(HeldComponentRight == HeldComponentLeft)
			{
				HeldComponentLeft =  nullptr;
			}
		}
	}
}

void AVRPawn::ReleaseRightGrab()
{
	if(HeldComponentRight)
	{
		
		if(HeldComponentRight->TryRelease())
		{
			HeldComponentRight = nullptr;
		}
	}
}

void AVRPawn::TriggerLeft()
{
	if(IsValid(HeldComponentLeft))
	{
		IVRInteractionAPI* Interface = Cast<IVRInteractionAPI>(HeldComponentLeft);
		if(Interface)
		{
			Interface->TriggerPressed();
		}
		
	}
}

void AVRPawn::TriggerReleasedLeft()
{
	if(IsValid(HeldComponentLeft))
	{
		IVRInteractionAPI* Interface = Cast<IVRInteractionAPI>(HeldComponentLeft);
		if(Interface)
		{
			Interface->TriggerReleased();
		}
		
	}
}

void AVRPawn::TriggerRight()
{
	if(IsValid(HeldComponentRight))
	{
		IVRInteractionAPI* Interface = Cast<IVRInteractionAPI>(HeldComponentRight);
		if(Interface)
		{
			Interface->TriggerPressed();
		}
	}
}

void AVRPawn::TriggerReleasedRight()
{
	if(IsValid(HeldComponentRight))
	{
		IVRInteractionAPI* Interface = Cast<IVRInteractionAPI>(HeldComponentRight);
		if(Interface)
		{
			Interface->TriggerReleased();
		}
	}
}

void AVRPawn::TriggerLeftAxis(float AxisValue)
{
	if(IsValid(HeldComponentLeft))
	{
		IVRInteractionAPI* Interface = Cast<IVRInteractionAPI>(HeldComponentLeft);
		if(Interface)
		{
			Interface->TriggerAxis(AxisValue);
		}
		
	}
}

void AVRPawn::TriggerRightAxis(float AxisValue)
{
	if(IsValid(HeldComponentLeft))
	{
		IVRInteractionAPI* Interface = Cast<IVRInteractionAPI>(HeldComponentRight);
		if(Interface)
		{
			Interface->TriggerAxis(AxisValue);
		}
		
	}
}


