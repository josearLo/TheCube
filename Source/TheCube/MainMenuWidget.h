// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();
	virtual void NativeConstruct() override;
	UFUNCTION()
	UWidget* GetFirstFocusableWidget() const;
	UPROPERTY()
	class ACubeController* ControlPersonaje;
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* PlayGameBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameBtn;

	UFUNCTION()
	void PlayGameClicked();

	UFUNCTION()
	void QuitGameClicked();
private:

	void EnableWidgetNavigation();

	UFUNCTION()
	void PlayHoverSound();

	UFUNCTION()
	void PlayPressedSound();

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* HoverSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* PressedSound;

	//Bools para controlar el color de los botones en mi widget como esta en Tick ocupamos que sea solo una vez
	bool bAlreadyPlayGame = false;
	bool bAlreadyQtBtn = false;
};
