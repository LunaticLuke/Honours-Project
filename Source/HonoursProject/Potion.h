// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Potion.generated.h"

UCLASS()
class HONOURSPROJECT_API APotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PotionBottleMesh;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* PotionMaterial;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable)
	void SetProgram(TArray<struct FVariableProgramData> VariableArray, TArray<class AFunctionNode*> ProgramArrayParam, TArray<class AVariableNodeActor*>VariableNodeActors);
	UPROPERTY(EditAnywhere)
	TArray<class AVariableNodeActor*> ProgramVariables;
	UPROPERTY(EditAnywhere)
	TArray<class AFunctionNode*> ProgramArray;
	UPROPERTY(EditAnywhere)
	TArray<FVariableProgramData> VariableData;
};
