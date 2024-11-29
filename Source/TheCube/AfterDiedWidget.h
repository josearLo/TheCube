// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AfterDiedWidget.generated.h"

class UButton;
class USoundBase;

UCLASS()
class THECUBE_API UAfterDiedWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;
	UFUNCTION()
	UWidget* GetFirstFocusableWidget() const;
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitToMain;

	virtual bool Initialize() override;

	UFUNCTION()
	void PlayGameClicked();

	UFUNCTION()
	void QuitGameClicked();

	void EnableWidgetNavigation();

	void PlayHoverSound();

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* HoverSound;

	bool bResume = false;
	bool bQuit = false;
};
