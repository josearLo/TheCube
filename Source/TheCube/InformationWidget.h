// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API UInformationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;
	UFUNCTION()
	UWidget* GetFirstFocusableWidget() const;
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeBtn;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TxtInfo;

	virtual bool Initialize() override;
	UFUNCTION()
	void OkButtonPressed();
	void EnableWidgetNavigation();
};
