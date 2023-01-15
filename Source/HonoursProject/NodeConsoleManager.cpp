// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeConsoleManager.h"
#include "CreateVariableMachine.h"
#include "ProgramConsoleLogUI.h"
#include "ProgramExecutionUI.h"
#include "VariableListUI.h"

// Sets default values
ANodeConsoleManager::ANodeConsoleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VariableListMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Variable List Mesh"));
	SetRootComponent(VariableListMesh);
	
	VariableListUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Variable List UI"));
	VariableListUI->SetupAttachment(VariableListMesh);

	ProgramConsoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Program Console Mesh"));
	ProgramConsoleOutputUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Program Console Output UI"));
	ProgramConsoleOutputUI->SetupAttachment(ProgramConsoleMesh);

	ProgramExecutionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Program Execution Mesh"));
	ProgramExecutionUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Program Execution UI"));
	ProgramExecutionUI->SetupAttachment(ProgramExecutionMesh);
	
}

// Called when the game starts or when spawned
void ANodeConsoleManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANodeConsoleManager::DisplayUI()
{
}

// Called every frame
void ANodeConsoleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANodeConsoleManager::AddToLog(FString StringToAdd)
{
	Cast<UProgramConsoleLogUI>(ProgramConsoleOutputUI->GetWidget())->AddOutput(StringToAdd);
}

void ANodeConsoleManager::DisplayVariable(AVariableNodeActor* VariableToAdd)
{
	Cast<UVariableListUI>(VariableListUI->GetWidget())->DisplayVariables(VariableToAdd);
}

void ANodeConsoleManager::DisplayProgramExecution(AFunctionNode* NodeToAdd)
{
	Cast<UProgramExecutionUI>(ProgramExecutionUI->GetWidget())->DisplayProgram(NodeToAdd);
}

void ANodeConsoleManager::ClearLog()
{
	Cast<UProgramConsoleLogUI>(ProgramConsoleOutputUI->GetWidget())->ClearLog();
	Cast<UVariableListUI>(VariableListUI->GetWidget())->ClearVariableLog();
	Cast<UProgramExecutionUI>(ProgramExecutionUI->GetWidget())->ClearLog();
}

