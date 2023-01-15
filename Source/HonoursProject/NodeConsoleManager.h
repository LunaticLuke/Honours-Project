// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "NodeConsoleManager.generated.h"


class UVariableConsoleUI;

UCLASS()
class HONOURSPROJECT_API ANodeConsoleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeConsoleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FString> ConsoleLog;
	UPROPERTY(Category="User Interface",EditAnywhere)
	UWidgetComponent* VariableListUI; //List Of Variables In The Program
	UPROPERTY(Category="User Interface",EditAnywhere)
	UWidgetComponent* ProgramConsoleOutputUI; //Console output as program progresses.
	UPROPERTY(Category="User Interface",EditAnywhere)
	UWidgetComponent* ProgramExecutionUI; //Shows the program structure.
	UPROPERTY(Category="Settings",EditAnywhere)
	int MaxOutputLog = 5;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VariableListMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProgramConsoleMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProgramExecutionMesh;
	
	void DisplayUI();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddToLog(FString StringToAdd);

	void DisplayVariable(class AVariableNodeActor* VariableToAdd);

	void DisplayProgramExecution(class AFunctionNode* NodeToAdd);

	void ClearLog();
	

};
