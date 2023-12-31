// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class FINALPRACTICECHAR_API ATPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultIMC;

	virtual void BeginPlay() override;
};
