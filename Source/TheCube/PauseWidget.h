// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

UCLASS()
class THECUBE_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;
	UFUNCTION()
	UWidget* GetFirstFocusableWidget() const;
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitToMain;

	virtual bool Initialize() override;
	UFUNCTION()
	void ResumeBtnClicked();

	UFUNCTION()
	void MainMenuBtnClicked();
	void EnableWidgetNavigation();
protected:

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* HoverSound;

	bool bResume = false;
	bool bQuit = false;
	
	void PlayHoverSound();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
