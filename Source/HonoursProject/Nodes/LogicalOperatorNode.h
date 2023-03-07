// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionNode.h"
#include "LogicalOperatorNode.generated.h"

UENUM()
enum class ELogicalOperators {
	Or UMETA(DisplayName = "|| (OR)"),
	And UMETA(DisplayName = "&& (AND)"),
	Not UMETA(DisplayName = "! (NOT)") };
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API ALogicalOperatorNode : public AFunctionNode
{
	GENERATED_BODY()

	ALogicalOperatorNode();

public:
	ELogicalOperators GetLogicalOperator();
	
protected:

	virtual void BeginPlay() override;
	
	virtual void ExecuteNode() override;

	virtual bool IsThereCompileError() override;

	virtual void DisplayText() override;
	
	UPROPERTY(EditAnywhere)
	ELogicalOperators LogicalOperator;

	
	
	
};
