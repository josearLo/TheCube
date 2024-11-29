// Fill out your copyright notice in the Description page of Project Settings.


#include "InformationWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "CubeController.h"

void UInformationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!ResumeBtn->HasKeyboardFocus())
	{
		ResumeBtn->SetKeyboardFocus();
		ResumeBtn->SetBackgroundColor(FLinearColor::Blue);
	}
}

void UInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ResumeBtn)
	{

		ResumeBtn->SetKeyboardFocus();

	}
}

UWidget* UInformationWidget::GetFirstFocusableWidget() const
{
	return ResumeBtn;
}

bool UInformationWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (ResumeBtn)
	{
		ResumeBtn->OnClicked.AddDynamic(this, &UInformationWidget::OkButtonPressed);
	}
	return true;
}

void UInformationWidget::OkButtonPressed()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController))
	{
		//CubeController->bGoalWidget = false;
		CubeController->RemoveInfoWidget();
	}
}
void UInformationWidget::EnableWidgetNavigation()
{
	UWidget* FirstWidget = GetFirstFocusableWidget();
	if (FirstWidget)
	{
		FirstWidget->SetKeyboardFocus();
		//FirstWidget->SetFocus();


	}
}