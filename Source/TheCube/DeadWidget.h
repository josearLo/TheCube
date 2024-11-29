// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API UDeadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DeadText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RandomText")
	TArray<FString> RandomTextList;  // Lista de textos aleatorios
};
