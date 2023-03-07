// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Requests/CustomerRequest.h"
#include "Customer.generated.h"

class AFunctionNode;
struct FVariableRequest;
class ATargetPoint;


UCLASS()
class HONOURSPROJECT_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	ATargetPoint* ServingPoint;
	
	UPROPERTY(EditAnywhere)
	ATargetPoint* ExitPoint;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CustomerMesh;
	UPROPERTY(EditAnywhere)
	class UCustomerRequest* CurrentRequest;

	void AreRequestedVariablesFound();

	bool CheckVariableName(FString NameToCheck);

	void CheckProgramExecution();
	UPROPERTY(EditAnywhere)
	class APotion* CurrentPotion;

	bool CheckArithmeticOperator(AFunctionNode* NodeToCheck, struct FFunctionRequest RequestToCheck);

	bool CheckParameters(AFunctionNode* NodeToCheck,  FFunctionRequest RequestToCheck);

	bool CheckLogicalOperator(AActor* NodeToCheck, FParameterRequest ReqToCheck);

	bool CheckRelationalOperator(AActor* NodeToCheck, FParameterRequest ReqToCheck);

	double GetParameterNumberValue(AFunctionNode* NodeToCheck, int Index);
	
	FString GetParameterTextValue(AFunctionNode* NodeToCheck, int Index);

	bool CheckInnerParameter(AActor* NodeToCheck, int Index, double ValueToCheck, FString TextToCheck);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToCounter();

	void MoveToExit();

	bool bReachedDestination = false;

	void SetRequest(UCustomerRequest* RequestToSet);

	void SetPotion(APotion* PotionToSet);

	void VariableCheck();
};


