// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CustomerRequest.generated.h"

enum class ERelationalOperators;
enum class ELogicalOperators;
enum class ArithmeticOperatorType;
enum class NodeDataTypes : uint8;

// This struct will store the details of any specific variables that are expected in the customer's program
USTRUCT()
struct FParameterRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	bool bSpecificValue = false;
	UPROPERTY(EditAnywhere)
	double RequiredParamNumValue;
	UPROPERTY(EditAnywhere)
	FString RequiredParamTextValue;
	UPROPERTY(EditAnywhere)
	bool bSpecificParameterDataType = false;
	UPROPERTY(EditAnywhere)
	UClass* TypeOfParameter;
	UPROPERTY(EditAnywhere)
	bool bSpecificLogicalOperatorTypeRequired = false;
	UPROPERTY(EditAnywhere)
	ELogicalOperators LogicalOperatorTypeRequired;
	UPROPERTY(EditAnywhere)
	bool bSpecificRelationalOperatorNodeRequired = false;
	UPROPERTY(EditAnywhere)
	ERelationalOperators RelationalOperatorRequired;
	UPROPERTY(EditAnywhere)
	bool bSpecificParam1Value = false;
	UPROPERTY(EditAnywhere)
	double RequestedParam1NumValue;
	UPROPERTY(EditAnywhere)
	FString RequestedParam1TextValue;
	UPROPERTY(EditAnywhere)
	bool bSpecificParam2Value = false;
	UPROPERTY(EditAnywhere)
	double RequestedParam2NumValue;
	UPROPERTY(EditAnywhere)
	FString RequestedParam2TextValue;
};
USTRUCT()
struct FVariableRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	bool bSpecificName = false; //Does this request require a specific variable name.
	UPROPERTY(EditAnywhere)
	FString RequiredName; //If so, what is it.
	UPROPERTY(EditAnywhere)
	TArray<NodeDataTypes> RequiredDataTypes;
	UPROPERTY(EditAnywhere)
	bool bSpecificStartingValue = false; //Does this request require this variable to have a specific starting value?
	UPROPERTY(EditAnywhere)
	FString RequiredTextStartingValue;
	UPROPERTY(EditAnywhere)
	double RequiredNumberStartingValue;
	UPROPERTY(EditAnywhere)
	bool bSpecificEndingValue = false;
	UPROPERTY(EditAnywhere)
	FString RequiredTextValue;
	UPROPERTY(EditAnywhere)
	double RequiredNumberValue;

	class AVariableNodeActor* Actor;
	UPROPERTY(EditAnywhere)
	bool bFoundWithinProgram = false;
};

USTRUCT()
struct FFunctionRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UClass* RequiredNodeType;
	UPROPERTY(EditAnywhere)
	bool bSpecificArithmeticOperator = false;
	UPROPERTY(EditAnywhere)
	ArithmeticOperatorType ArithmeticOperatorTypeRequired;
	UPROPERTY(EditAnywhere)
	TArray<FParameterRequest> RequestedParameters;
	UPROPERTY(EditAnywhere)
	bool bFoundWithinProgram = false;
};


/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API UCustomerRequest : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString CustomerRequestDialogue;

	//Array of specific variables expected within the program, if any.
	UPROPERTY(EditAnywhere)
	TArray<FVariableRequest> RequestedVariables;
	UPROPERTY(EditAnywhere)
	TArray<FFunctionRequest> RequestedFunctions;

	//An Array Of Variable Names That Would Be Good Naming Choices For This Customer's program (used within variable creation machine)
	UPROPERTY(EditAnywhere)
	TArray<FString> SuggestedVariableNames;
};
