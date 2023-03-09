// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManager.h"

#include "CustomerManager.h"
#include "TutorialUI.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATutorialManager::ATutorialManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tutorial UI"));
}

// Called when the game starts or when spawned
void ATutorialManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&ATutorialManager::CheckProgress,0.2f,true,0.2f);
	TutorialUI = Cast<UTutorialUI>(WidgetComponent->GetWidget());
}

void ATutorialManager::CheckProgress()
{
	float NPCDistance,PlayerDistance;
	switch (TutorialTasks[CurrentTaskNumber].TutorialTaskType)
	{
	case ETutorialTaskType::Slides:
		if(TutorialUI->GetCurrentSlideNumber() >= TutorialTasks[CurrentTaskNumber].TargetSlideNumber)
		{
			TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
			CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
		}
		break;
	case ETutorialTaskType::Follow:
		AActor* TargetLocation;
		TargetLocation = *LocationMap.Find(TutorialTasks[CurrentTaskNumber].TargetLocation);
		NPCDistance = FVector::Distance(NPCHelper->GetActorLocation(),TargetLocation->GetActorLocation());
		PlayerDistance = FVector::Distance(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation(),NPCHelper->GetActorLocation());

		if(NPCDistance <= 200.0f && PlayerDistance <= 200.0f)
		{
			TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
			CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
		}
		break;
	case ETutorialTaskType::Quiz:
		if(QuizAnswer == TutorialTasks[CurrentTaskNumber].CorrectAnswer)
		{
			TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
			CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
			QuizAnswer = "";
		}
		break;
	case ETutorialTaskType::Customers:
	if(CustomerManager->GetServedCustomers() >= TutorialTasks[CurrentTaskNumber].TargetCustomersServed)
	{
		TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
		CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
	}
		break;
	default: ;
	}
}

// Called every frame
void ATutorialManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

