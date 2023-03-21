// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialManager.h"

#include "AnswerBlock.h"
#include "CustomerManager.h"
#include "NPCHelper.h"
#include "TutorialUI.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATutorialManager::ATutorialManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tutorial UI"));

	QuizWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Quiz UI"));

	AnswerBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Answer Box Mesh"));
}

// Called when the game starts or when spawned
void ATutorialManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&ATutorialManager::CheckProgress,0.2f,true,0.2f);
	TutorialUI = Cast<UTutorialUI>(WidgetComponent->GetWidget());
	TutorialUI->SetQuiz(false);
	QuizUI = Cast<UTutorialUI>(QuizWidgetComponent->GetWidget());
	QuizUI->SetQuiz(true);
	AnswerBoxMesh->OnComponentBeginOverlap.AddDynamic(this,&ATutorialManager::OnParameterOverlap);
	SetupTask();
}

void ATutorialManager::OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Cyan,TEXT("Hit"));
	if(OtherActor->IsA(AAnswerBlock::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1,50.0f,FColor::Cyan,TEXT("Answer Block"));

		QuizAnswer = Cast<AAnswerBlock>(OtherActor)->GetAnswer();
	}
}

void ATutorialManager::CheckProgress()
{
	float NPCDistance,PlayerDistance;
	if(!bActiveAction)
	{
		switch (TutorialTasks[CurrentTaskNumber].TutorialTaskType)
		{
		case ETutorialTaskType::Slides:
			//If the current slide number is greater than the desired slide number, task is fulfilled.
			if(TutorialUI->GetCurrentSlideNumber() >= TutorialTasks[CurrentTaskNumber].TargetSlideNumber )
			{
				//If this task isn't marked as completed.
				if(!TutorialTasks[CurrentTaskNumber].bCompletedTask)
				{
					//If this task has a post task action, this needs to be completed before advancing to the next task
					if(TutorialTasks[CurrentTaskNumber].bPostTaskAction)
					{
						CarryOutPostTaskAction();
					}
					else //Not post task action so just move onto the next task
					{
						TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
						CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
						SetupTask();
					}
				}
				else //Post task action completed
				{
					CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
					SetupTask();
				}
				
			}
			
			
			break;
		case ETutorialTaskType::Follow:
			AActor* TargetLocation;
			TargetLocation = *LocationMap.Find(TutorialTasks[CurrentTaskNumber].TargetLocation);
			NPCDistance = FVector::Distance(NPCHelper->GetActorLocation(),TargetLocation->GetActorLocation());
			PlayerDistance = FVector::Distance(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation(),NPCHelper->GetActorLocation());

			if(NPCDistance <= 200.0f && PlayerDistance <= 200.0f)
			{
				if(!TutorialTasks[CurrentTaskNumber].bCompletedTask)
				{
					//If this task has a post task action, this needs to be completed before advancing to the next task
					if(TutorialTasks[CurrentTaskNumber].bPostTaskAction)
					{
						CarryOutPostTaskAction();
					}
					else //Not post task action so just move onto the next task
						{
						TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
						CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
						SetupTask();
						}
				}
				else //Post task action completed
					{
					CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
					SetupTask();
					}
			}
			break;
		case ETutorialTaskType::Quiz:
			if(QuizAnswer == TutorialTasks[CurrentTaskNumber].CorrectAnswer)
			{
				if(!TutorialTasks[CurrentTaskNumber].bCompletedTask)
				{
					//If this task has a post task action, this needs to be completed before advancing to the next task
					if(TutorialTasks[CurrentTaskNumber].bPostTaskAction)
					{
						CarryOutPostTaskAction();
					}
					else //Not post task action so just move onto the next task
						{
						TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
						CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
						SetupTask();
						QuizAnswer = "";
						CurrentQuizQuestion = FMath::Clamp(CurrentQuizQuestion + 1, 0, QuizQuestions.Num() - 1);
						QuizUI->SetQuizNumber(CurrentQuizQuestion);
						QuizUI->ShowImage(false);
						}
				}
				else //Post task action completed
					{
					CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
					SetupTask();
					QuizAnswer = "";
					CurrentQuizQuestion = FMath::Clamp(CurrentQuizQuestion + 1, 0, QuizQuestions.Num() - 1);
					QuizUI->SetQuizNumber(CurrentQuizQuestion);
					QuizUI->ShowImage(false);
					}
			}
			else
			{
				if(QuizAnswer != "")
				{
				
				}
			}
			break;
		case ETutorialTaskType::Customers:
			if(CustomerManager->GetServedCustomers() >= TutorialTasks[CurrentTaskNumber].TargetCustomersServed)
			{
				if(!TutorialTasks[CurrentTaskNumber].bCompletedTask)
				{
					//If this task has a post task action, this needs to be completed before advancing to the next task
					if(TutorialTasks[CurrentTaskNumber].bPostTaskAction)
					{
						CarryOutPostTaskAction();
					}
					else //Not post task action so just move onto the next task
						{
						TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
						CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
						SetupTask();
						}
				}
				else //Post task action completed
					{
					CurrentTaskNumber = FMath::Clamp(CurrentTaskNumber + 1,0,TutorialTasks.Num() - 1);
					SetupTask();
					}
			}
			break;
		default: ;
		}
	}
}

void ATutorialManager::SetupTask()
{
	for(int i = 0; i < AnswerBlocks.Num();i++)
	{
		AnswerBlocks[i]->SetActorHiddenInGame(true);
		AnswerBlocks[i]->SetActorEnableCollision(false);
	}
	CustomerManager->AllowCustomers(TutorialTasks[CurrentTaskNumber].bAllowCustomers);
	switch (TutorialTasks[CurrentTaskNumber].TutorialTaskType)
	{
	case ETutorialTaskType::Slides: break;
	case ETutorialTaskType::Follow:
		NPCHelper->MoveToLocation(*LocationMap.Find(TutorialTasks[CurrentTaskNumber].TargetLocation));
		break;
	case ETutorialTaskType::Quiz:
		QuizUI->ShowImage(true);
		for(int i = 0; i < QuizQuestions[CurrentQuizQuestion].PotentialAnswers.Num();i++)
		{
			AnswerBlocks[i]->SetAnswer(QuizQuestions[CurrentQuizQuestion].PotentialAnswers[i]);
			AnswerBlocks[i]->SetActorLocation(BlocksSpawnPoint->GetActorLocation());
			AnswerBlocks[i]->SetActorHiddenInGame(false);
			AnswerBlocks[i]->SetActorEnableCollision(true);
		}
		break;
	case ETutorialTaskType::Customers: break;
	default: ;
	}
	if(TutorialTasks[CurrentTaskNumber].bPreTaskAction)
	{
		CarryOutPreTaskAction();
	}
}

void ATutorialManager::CarryOutPreTaskAction()
{
	bActiveAction = true;
	float Timer = TutorialTasks[CurrentTaskNumber].PreTaskAction.LengthOfAction;
	switch (TutorialTasks[CurrentTaskNumber].PreTaskAction.TypeOfAction) {

	case ENPCActionType::Talking:
		NPCHelper->bTalking = true;
		ShowPreDialogue();
		break;
	case ENPCActionType::PickUpItem:
		NPCHelper->bPickingUp = true;
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this, &ATutorialManager::EndPreTaskAction,Timer,false,Timer);
		break;
	case ENPCActionType::DropItem:
		NPCHelper->bPuttingDown = true;
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this, &ATutorialManager::EndPreTaskAction,Timer,false,Timer);
		break;
	default: ;
	}
	

}

void ATutorialManager::CarryOutPostTaskAction()
{
	bActiveAction = true;
	float Timer = TutorialTasks[CurrentTaskNumber].PostTaskAction.LengthOfAction;
	switch (TutorialTasks[CurrentTaskNumber].PostTaskAction.TypeOfAction) {

	case ENPCActionType::Talking:
		NPCHelper->bTalking = true;
		ShowPostDialogue();
		break;
	case ENPCActionType::PickUpItem:
		NPCHelper->bPickingUp = true;
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this, &ATutorialManager::EndPostTaskAction,Timer,false,Timer);
		break;
	case ENPCActionType::DropItem:
		NPCHelper->bPuttingDown = true;
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this, &ATutorialManager::EndPostTaskAction,Timer,false,Timer);
		break;
	default: ;
	}
}

void ATutorialManager::ShowPreDialogue()
{
	if(CurrentDialogueNumber < TutorialTasks[CurrentTaskNumber].PreTaskAction.Dialogue.Num())
	{
		float Timer = TutorialTasks[CurrentTaskNumber].PreTaskAction.TimeDialogueOnScreen[CurrentDialogueNumber];
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this, &ATutorialManager::ShowPreDialogue,Timer,false,Timer);
		GEngine->AddOnScreenDebugMessage(0,Timer,FColor::Cyan,TutorialTasks[CurrentTaskNumber].PreTaskAction.Dialogue[CurrentDialogueNumber]);
		CurrentDialogueNumber++;
	}
	else
	{
		bActiveAction = false;
		CurrentDialogueNumber = 0;
		NPCHelper->bTalking = false;
	}
}

void ATutorialManager::ShowPostDialogue()
{
	if(CurrentDialogueNumber < TutorialTasks[CurrentTaskNumber].PostTaskAction.Dialogue.Num())
	{
		float Timer = TutorialTasks[CurrentTaskNumber].PostTaskAction.TimeDialogueOnScreen[CurrentDialogueNumber];
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this, &ATutorialManager::ShowPostDialogue,Timer,false,Timer);
		GEngine->AddOnScreenDebugMessage(0,Timer,FColor::Cyan,TutorialTasks[CurrentTaskNumber].PostTaskAction.Dialogue[CurrentDialogueNumber]);
		CurrentDialogueNumber++;
	}
	else
	{
		bActiveAction = false;
		CurrentDialogueNumber = 0;
		TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
		NPCHelper->bTalking = false;
	}
}


void ATutorialManager::EndPreTaskAction()
{
	bActiveAction = false;
	NPCHelper->bTalking = false;
	NPCHelper->bPickingUp = false;
	NPCHelper->bTalking = false;
}

void ATutorialManager::EndPostTaskAction()
{
	bActiveAction = false;
	TutorialTasks[CurrentTaskNumber].bCompletedTask = true;
	NPCHelper->bTalking = false;
	NPCHelper->bPickingUp = false;
	NPCHelper->bTalking = false;
}

// Called every frame
void ATutorialManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

