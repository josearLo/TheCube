// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "CubeController.h"


void UGoalWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!OkBtn->HasKeyboardFocus())
	{
		OkBtn->SetKeyboardFocus();
		OkBtn->SetBackgroundColor(FLinearColor::Blue);
	}
}

void UGoalWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (OkBtn)
	{

		OkBtn->SetKeyboardFocus();

	}
}

UWidget* UGoalWidget::GetFirstFocusableWidget() const
{
	return OkBtn;
}

bool UGoalWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (OkBtn)
	{
		OkBtn->OnClicked.AddDynamic(this, &UGoalWidget::CloseWidget);
	}
	return true;
}

void UGoalWidget::CloseWidget()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
	{
		CubeController->bGoalWidget = false;
		CubeController->RemoveGoalWidget();
	}
}

void UGoalWidget::EnableWidgetNavigation()
{
	UWidget* FirstWidget = GetFirstFocusableWidget();
	if (FirstWidget)
	{
		FirstWidget->SetKeyboardFocus();
		//FirstWidget->SetFocus();


	}
}
