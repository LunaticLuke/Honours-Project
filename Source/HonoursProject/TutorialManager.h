// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialManager.generated.h"


class UPointLightComponent;
class AAnswerBlock;
class ANPCHelper;
class ACustomerManager;
class UWidgetComponent;
class UTutorialUI;

UENUM()
enum class ETutorialLocations
{
	StartingFire,
	VariableMachine,
	CustomerCounter,
	Cauldron,
	CentreTable
};

UENUM()
enum class ESlideTopic
{
	DataTypes_Variables,
	For_Loops,
	Conditionals,
	While_Loops
};

UENUM()
enum class ETutorialTaskType
{
	Slides,
	Follow,
	Quiz,
	Customers
};

UENUM()
enum class ENPCActionType
{
	Talking,
	PickUpItem,
	DropItem
};

USTRUCT()
struct FNPCAction
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	ENPCActionType TypeOfAction;
	UPROPERTY(EditAnywhere)
	TArray<FString> Dialogue;
	UPROPERTY(EditAnywhere)
	TArray<float> TimeDialogueOnScreen;
	UPROPERTY(EditAnywhere)
	AActor* ItemToInteract;
	UPROPERTY(EditAnywhere)
	float LengthOfAction;
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

	UPROPERTY(EditAnywhere)
	bool bAllowCustomers = false;
	
	//Has this task been completed?
	UPROPERTY(EditAnywhere)
	bool bCompletedTask = false;
	
	UPROPERTY(EditAnywhere)
	bool bPreTaskAction = false;
	
	UPROPERTY(EditAnywhere)
	FNPCAction PreTaskAction;
	
	UPROPERTY(EditAnywhere)
	bool bPostTaskAction = false;
	
	UPROPERTY(EditAnywhere)
	FNPCAction PostTaskAction;
};

USTRUCT()
struct FQuizQuestion
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FString> PotentialAnswers;
	
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
	virtual void OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
	UFUNCTION()
	void CheckProgress();

	FTimerHandle Ticker;

	int CurrentTaskNumber = 0;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* WidgetComponent;
	UPROPERTY(EditAnywhere)
	UTutorialUI* TutorialUI;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* QuizWidgetComponent;
	UPROPERTY(EditAnywhere)
	UTutorialUI* QuizUI;
	
	UPROPERTY(EditAnywhere)
	FString QuizAnswer = "";
	
	UPROPERTY(EditAnywhere)
	ACustomerManager* CustomerManager;

	UPROPERTY(EditAnywhere)
	ANPCHelper* NPCHelper;

	void SetupTask();

	UPROPERTY(EditAnywhere)
	TArray<AAnswerBlock*> AnswerBlocks;
	
	UPROPERTY(EditAnywhere)
	TArray<FQuizQuestion> QuizQuestions;
	UPROPERTY(EditAnywhere)
	AActor* BlocksSpawnPoint;

	int CurrentQuizQuestion = 0;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* AnswerBoxMesh;

	FTimerHandle ActionTimer;

	UFUNCTION()
	void CarryOutPreTaskAction();
	
	UFUNCTION()
	void CarryOutPostTaskAction();
	
	UFUNCTION()
	void ShowPreDialogue();

	UFUNCTION()
	void ShowPostDialogue();
	
	UFUNCTION(BlueprintCallable)
	void EndPreTaskAction();
	
	UFUNCTION(BlueprintCallable)
	void EndPostTaskAction();
	
	bool bActiveAction = false;

	bool bPreTaskAction = false;

	bool bPostTaskAction = false;
	
	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight;

	bool bLightLerping = false;

	int CurrentDialogueNumber = 0;

	float lerpNumber = 0;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
