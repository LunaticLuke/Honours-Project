// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialManager.generated.h"


class ACustomerManager;
class UWidgetComponent;
class UTutorialUI;

UENUM()
enum class ETutorialLocations
{
	StartingFire,
	VariableMachine,
	CustomerCounter,
	Cauldron
};

UENUM()
enum class ESlideTopic
{
	DataTypes_Variables,
	Arithmetic,
	Conditionals,
	Loops
};

UENUM()
enum class ETutorialTaskType
{
	Slides,
	Follow,
	Quiz,
	Customers
};

USTRUCT()
struct FTutorialTask
{
	GENERATED_BODY()
	//Type of tutorial task
	UPROPERTY(EditAnywhere)
	ETutorialTaskType TutorialTaskType;
	
	//Where should the player and NPC walk to (If Follow Task)
	UPROPERTY(EditAnywhere)
	ETutorialLocations TargetLocation;

	UPROPERTY(EditAnywhere)
	ESlideTopic TargetSlideTopic;
	
	//What slide number is needed for this task to be deemed complete (If slide task)
	UPROPERTY(EditAnywhere)
	int TargetSlideNumber;
	
	//How many customers need to have been served for this task to have completed (If Customer Task)
	UPROPERTY(EditAnywhere)
	int TargetCustomersServed;

	//The correct answer to this question (If quiz type)
	UPROPERTY(EditAnywhere)
	FString CorrectAnswer;

	//Has this task been completed?
	UPROPERTY(EditAnywhere)
	bool bCompletedTask = false;
};


UCLASS()
class HONOURSPROJECT_API ATutorialManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ESlideTopic CurrentSlideTopic = ESlideTopic::DataTypes_Variables;
	
	UPROPERTY(EditAnywhere)
	TMap<ETutorialLocations,AActor*> LocationMap;
	
	UPROPERTY(EditAnywhere)
	TArray<FTutorialTask> TutorialTasks;
	

	
	UFUNCTION()
	void CheckProgress();

	FTimerHandle Ticker;

	int CurrentTaskNumber = 0;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* WidgetComponent;
	
	UTutorialUI* TutorialUI;
	UPROPERTY(EditAnywhere)
	FString QuizAnswer = "";
	
	UPROPERTY(EditAnywhere)
	ACustomerManager* CustomerManager;

	UPROPERTY(EditAnywhere)
	AActor* NPCHelper;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
