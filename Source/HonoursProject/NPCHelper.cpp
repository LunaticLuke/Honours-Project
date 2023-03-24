// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCHelper.h"

#include "CustomerAIController.h"
#include "SpeechBubbleUI.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ANPCHelper::ANPCHelper()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ACustomerAIController::StaticClass();

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPCHelper::BeginPlay()
{
	Super::BeginPlay();
	SpeechBubbleUI = Cast<USpeechBubbleUI>(WidgetComponent->GetWidget());
	if(SpeechBubbleUI)
	{
		GEngine->AddOnScreenDebugMessage(0,5.0f,FColor::Magenta,TEXT("Successfully Got UI"));
	}
}

// Called every frame
void ANPCHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(SpeechBubbleUI && UnassignedText != "")
	{
		SpeechBubbleUI->SetText(UnassignedText);
		UnassignedText = "";
	}
	
	
	//FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->GetComponentLocation(),UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
	//WidgetComponent->SetWorldRotation(lookAt);
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

void ANPCHelper::SetText(FString TextToSet)
{
	//Cast<USpeechBubbleUI>(WidgetComponent->GetWidget())->SetText(TextToSet);
	if(SpeechBubbleUI)
	{
		SpeechBubbleUI->SetText(TextToSet);
	}
	else
	{
		UnassignedText = TextToSet;
	}
}

void ANPCHelper::ShowUI(bool bShow)
{
	
	
	if(SpeechBubbleUI)
	{
		SpeechBubbleUI->ShowUI(bShow);
	}
	
}

void ANPCHelper::SetInteractItem(AActor* ItemToSet)
{
	ItemToInteractWith = ItemToSet;
}

void ANPCHelper::PickUpDrop()
{
	if(bPickingUp)
	{
		Cast<UPrimitiveComponent>(ItemToInteractWith->GetRootComponent())->SetSimulatePhysics(false);
		ItemToInteractWith->SetActorEnableCollision(false);
		ItemToInteractWith->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("Hand"));
		//Item->SetActorLocation(GetActorLocation());
	}
	else
	{
		Cast<UPrimitiveComponent>(ItemToInteractWith->GetRootComponent())->SetSimulatePhysics(true);
		ItemToInteractWith->SetActorEnableCollision(true);
		ItemToInteractWith->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
}



