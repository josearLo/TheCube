// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControllerWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API UControllerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;
	UFUNCTION()
	UWidget* GetFirstFocusableWidget() const;
	void EnableWidgetNavigation();
	UPROPERTY(meta = (BindWidget))
	class UButton* OkBtn;

	virtual bool Initialize() override;

	UFUNCTION()
	void OkBtnClicked();
};
