// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCHelper.generated.h"


class USpeechBubbleUI;
UCLASS()
class HONOURSPROJECT_API ANPCHelper : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCHelper();
	UPROPERTY(BlueprintReadWrite)
	bool bTalking = false;
	UPROPERTY(BlueprintReadWrite)
	bool bPickingUp = false;
	UPROPERTY(BlueprintReadWrite)
	bool bPuttingDown = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UWidgetComponent* WidgetComponent;
	UPROPERTY(EditAnywhere)
	USpeechBubbleUI* SpeechBubbleUI;

	FString UnassignedText = "";

	AActor* ItemToInteractWith;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to inpute
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(AActor* LocationToTravelTo);

	void SetText(FString TextToSet);

	void ShowUI(bool bShow);

	void SetInteractItem(AActor* ItemToSet);
	UFUNCTION(BlueprintCallable)
	void PickUpDrop();
};
