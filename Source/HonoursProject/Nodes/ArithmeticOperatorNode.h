// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionNode.h"
#include "ArithmeticOperatorNode.generated.h"

UENUM()
enum class ArithmeticOperatorType
{
	Addition UMETA(DisplayName = "Addition"),
	Subtraction UMETA(DisplayName = "Subtraction"),
	Division UMETA(DisplayName = "Division"),
	Multiplication UMETA(DisplayName = "Multiplication"),
	Modulus UMETA(DisplayName = "Modulus")
};
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API AArithmeticOperatorNode : public AFunctionNode
{
	GENERATED_BODY()
	AArithmeticOperatorNode();

public:

	virtual void BeginPlay() override;
	
	virtual void ExecuteNode() override;

	virtual bool IsThereCompileError() override;

	virtual void DisplayText() override;

	ArithmeticOperatorType GetArithmeticOperatorType();
protected:
	UPROPERTY(EditAnywhere)
	ArithmeticOperatorType ArithmeticOperation;

	TArray<double> ParameterValues;
};
