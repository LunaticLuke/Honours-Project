// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnswerBlock.generated.h"

UCLASS()
class HONOURSPROJECT_API AAnswerBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnswerBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	FString Answer;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BlockMesh;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* TextComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString GetAnswer();

	void SetAnswer(FString AnswerToSet);
};
