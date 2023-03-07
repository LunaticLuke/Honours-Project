// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgramManager.generated.h"


class ANodeConsoleManager;
class AVariableConsoleUI;
//A struct that stores the current value of each variable in the program as well as the starting value;
USTRUCT(BlueprintType)
struct FVariableProgramData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FString StartingTextValue;
	UPROPERTY(EditAnywhere)
	FString CurrentTextValue;

	UPROPERTY(EditAnywhere)
	double StartingNumberValue;
	UPROPERTY(EditAnywhere)
	double CurrentNumberValue;
};

UCLASS()
class HONOURSPROJECT_API AProgramManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgramManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<class AFunctionNode*> ProgramExecution;
	UPROPERTY(EditAnywhere)
	ANodeConsoleManager* Console;

	AVariableConsoleUI* VariableUI;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<class AVariableNodeActor*> ProgramVariables;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FVariableProgramData> VariableData;

	void DisplayVariables();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void AddFunctionToProgram(AFunctionNode* FunctionToAdd);
	UFUNCTION(BlueprintCallable)
	void RunProgram();
	UFUNCTION(BlueprintCallable)
	void AddVariableToProgram(AVariableNodeActor* VariableToAdd);
	UFUNCTION(BlueprintCallable)
	AVariableNodeActor* GetVariableNode(FString VariableName);
	UFUNCTION(BlueprintCallable)
	void SetVariableValue(FString VariableName, FString TextValue, double NumberValue);

	ANodeConsoleManager* GetConsole();


};
