// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"

#include "Customer.h"
#include "CustomerRequestUI.h"
#include "Potion.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Requests/CustomerRequest.h"

// Sets default values
ACustomerManager::ACustomerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PotionTriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Potion Trigger Zone"));
	SetRootComponent(PotionTriggerZone);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Request UI"));

	CustomerLeaveZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Customer Leave Point"));
}

// Called when the game starts or when spawned
void ACustomerManager::BeginPlay()
{
	Super::BeginPlay();
	for(int i = 0; i < Requests.Num();i++)
	{
		for(int j = 0; j < Requests[i]->RequestedVariables.Num();j++)
		{
			Requests[i]->RequestedVariables[j].bFoundWithinProgram = false;
		}

		for(int j = 0; j < Requests[i]->RequestedFunctions.Num(); j++)
		{
			Requests[i]->RequestedFunctions[j].bFoundWithinProgram = false;
		}
	}

	PotionTriggerZone->OnComponentBeginOverlap.AddDynamic(this,&ACustomerManager::OnParameterOverlap);
	CustomerLeaveZone->OnComponentBeginOverlap.AddDynamic(this,&ACustomerManager::OnParameterOverlap);

	RequestUIClass = Cast<UCustomerRequestUI>(WidgetComponent->GetWidget());
	RequestUIClass->SetCustomerRequest("");
	RequestUIClass->SetCustomerFeedback("");
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&ACustomerManager::SpawnCustomer,5.0f,true,5.0f);
	Customer->SetActorHiddenInGame(true);
	Customer->SetActorEnableCollision(false);
}

void ACustomerManager::SpawnCustomer()
{
	if(CurrentRequestNumber < Requests.Num() && bCustomerCanEnter && !bCustomerAlreadyInShop)
	{
		Customer->SetRequest(Requests[CurrentRequestNumber]);
		RequestUIClass->SetCustomerRequest(Requests[CurrentRequestNumber]->CustomerRequestDialogue);
		Customer->MoveToCounter();
		bCustomerAlreadyInShop = true;
		CurrentRequestNumber++;
		Customer->SetActorHiddenInGame(false);
		Customer->SetActorEnableCollision(true);
		//Customer->VariableCheck();
	}
}

void ACustomerManager::OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if(OverlappedComponent == PotionTriggerZone)
	{
		if(OtherActor->IsA(APotion::StaticClass()) && bCustomerAlreadyInShop)
		{
			if(OtherActor->GetRootComponent()->IsSimulatingPhysics()) //Stops potion from being submitted whilst in the players hand, must have let go 
				{
				Customer->SetPotion(Cast<APotion>(OtherActor));
				Customer->VariableCheck();
				}
		}
	}else if(OverlappedComponent == CustomerLeaveZone)
	{
		if(OtherActor->IsA(ACustomer::StaticClass()))
		{
			Customer->SetActorHiddenInGame(true);
			Customer->SetActorEnableCollision(false);
			bCustomerAlreadyInShop = false;
		}
	}
}

// Called every frame
void ACustomerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

int ACustomerManager::GetServedCustomers()
{
	return ServedCustomers;
}

void ACustomerManager::AllowCustomers(bool bAllow)
{
	bCustomerCanEnter = bAllow;
}

