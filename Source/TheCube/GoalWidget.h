// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoalWidget.generated.h"

class UButton;

UCLASS()
class THECUBE_API UGoalWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* OkBtn;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;
	UFUNCTION()
	UWidget* GetFirstFocusableWidget() const;

	virtual bool Initialize() override;
	void EnableWidgetNavigation();
	UFUNCTION()
	void CloseWidget();
};
