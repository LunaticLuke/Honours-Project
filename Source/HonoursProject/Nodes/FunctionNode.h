// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeActor.h"
#include "HonoursProject/EnumManager.h"
#include "FunctionNode.generated.h"


USTRUCT()
struct FParameterInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FString ParameterName;
	UPROPERTY(EditAnywhere)
	class AVariableNodeActor* VariableNodeActor;
	UPROPERTY(EditAnywhere)
	class AFunctionNode* FunctionNodeActor;
	NodeDataTypes CurrentParameterDataType;
	//Stores whether this parameter has to be a variable (E.g, the left variable of an assignment has to be a variable to be assigned to, you cant assign to a function.
	bool VariableSlot = false; 
	UPROPERTY(EditAnywhere)
	TArray<NodeDataTypes> ValidDataTypes;
};
/**
 * 
 */
UCLASS()
class HONOURSPROJECT_API AFunctionNode : public ANodeActor
{
	GENERATED_BODY()

public:
	AFunctionNode();
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere)
	NodeDataTypes ReturnType = NodeDataTypes::Unassigned;

	
	/**
	 * @brief This function gets the return value of this particular node
	 * @param TextReturnValue This value is outputted if the return type ia text based (string & char)
	 * @param NumberReturnValue This value is outputted if the return type is number based (int,float and bool)
	 */
	void ReturnValue(FString& TextReturnValue, double& NumberReturnValue);

	FString GetWordReturnValue();

	double GetNumberReturnValue();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AFunctionNode* CurrentAttachedNode;
	UPROPERTY(BlueprintReadWrite)
	AFunctionNode* CurrentAttachedParent;
	UPROPERTY(BlueprintReadWrite)
	bool bAttachedToNode = false;
	UPROPERTY(BlueprintReadWrite)
	bool RootNode = true;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bWithinFunction = false;

	AActor* GetParameter(int Index);
protected:
	UPROPERTY(Category="Parameters",EditAnywhere)
	TArray<FParameterInfo> Parameters;

	/**
	 * @brief Checks that a parameter is valid to be added 
	 * @return Whether an error has been found or not
	 */
	virtual bool IsParameterSuitable(int ParameterNumber,AActor* NodeToSet);

	FString WordReturn;
	
	double NumberReturn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Parameter1Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Parameter2Mesh;

	UFUNCTION()
	virtual void OnParameterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
public:
	
	UFUNCTION(BlueprintCallable)
	virtual void ExecuteNode();
	/**
	 * @brief Checks for errors during program execution such as undeclared variables.
	 * @return Whether an error has been found or not
	 */
	virtual bool IsThereCompileError();


	
	
	UFUNCTION(BlueprintCallable)
	virtual void AddParameter(int ParameterNumber, AActor* NodeToSet);
};
