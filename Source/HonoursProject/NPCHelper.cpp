// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCHelper.h"

#include "CustomerAIController.h"

// Sets default values
ANPCHelper::ANPCHelper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ACustomerAIController::StaticClass();
}

// Called when the game starts or when spawned
void ANPCHelper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCHelper::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCHelper::MoveToLocation(AActor* LocationToTravelTo)
{
	Cast<ACustomerAIController>(GetController())->MoveCustomer(LocationToTravelTo->GetActorLocation());
}

