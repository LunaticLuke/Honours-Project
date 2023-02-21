// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeActor.h"
#include "HonoursProject/EnumManager.h"
#include "VariableNodeActor.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API AVariableNodeActor : public ANodeActor
{
	GENERATED_BODY()
public:
	
	AVariableNodeActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Variable Settings")
	//The data type of this Variable.
	NodeDataTypes VariableDataType = NodeDataTypes::Unassigned;
	UPROPERTY(EditAnywhere,Category="Variable Settings")
	FString VariableName;
	UPROPERTY(EditAnywhere,Category="Variable Settings")
	FString VariableValue;
	UPROPERTY(EditAnywhere,Category="Variable Settings")
	double VariableNumberValue;
	
	//Stores at what line of the current program the variable was declared.
	int LineDeclaredAt = -1;

	//Stores whether this variable has been assigned a value during this program.
	bool bAssignedTo =  false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetDataType(NodeDataTypes TypeToSet);
	
	NodeDataTypes GetDataType();

	void SetVariableValue(FString ValueToSet);

	FString GetVariableValue();

	void SetNumberValue(double NumberToSet);

	double GetNumberValue();

	void SetVariableName(FString NameToSet);

	FString GetVariableName();

	void SetLineDeclared(int LineToSet);

	int GetLineDeclaredAt();

	void SetVariableAssignedValueBool(bool BoolToSet);

	bool IsVariableAssignedValue();
	UPROPERTY(EditAnywhere,Category="Variable Settings")
	bool bUserCreated = false;
	UFUNCTION(BlueprintCallable)
	virtual void DisplayText() override;
	
};
