// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "CubeController.h"

void UControllerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OkBtn->HasKeyboardFocus() )
	{
		OkBtn->SetKeyboardFocus(); //bQuit
		OkBtn->SetBackgroundColor(FLinearColor::Blue);
	}
}

void UControllerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (OkBtn)
	{

		OkBtn->SetKeyboardFocus();

	}
}

UWidget* UControllerWidget::GetFirstFocusableWidget() const
{
	return OkBtn;
}

void UControllerWidget::EnableWidgetNavigation()
{
	UWidget* FirstWidget = GetFirstFocusableWidget();
	if (FirstWidget)
	{
		FirstWidget->SetKeyboardFocus();
		
	}
}

bool UControllerWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (OkBtn)
	{
		OkBtn->OnClicked.AddDynamic(this, &UControllerWidget::OkBtnClicked);
		//ResumeBtn->OnHovered.AddDynamic(this, &UAfterDiedWidget::PlayHoverSound);
		OkBtn->SetBackgroundColor(FLinearColor::Gray);

	}
	
	return true;
}

void UControllerWidget::OkBtnClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
	{
		CubeController->bGoalWidget = false;
		CubeController->RemoveControlWidget();
	}
	
}
