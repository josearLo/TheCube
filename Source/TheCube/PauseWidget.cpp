// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "CubeController.h"


void UPauseWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!ResumeBtn->HasKeyboardFocus() && !QuitToMain->HasKeyboardFocus())
	{
		ResumeBtn->SetKeyboardFocus(); //bQuit
	}
	if (ResumeBtn && QuitToMain)
	{
		if (ResumeBtn->HasKeyboardFocus() && !bResume)
		{
			bResume = true;
			bQuit = false;
			ResumeBtn->SetBackgroundColor(FLinearColor::Blue);

			QuitToMain->SetBackgroundColor(FLinearColor::Gray);
			PlayHoverSound();
		}
		else if (QuitToMain->HasKeyboardFocus() && !bQuit)
		{
			bQuit = true;
			bResume = false;

			ResumeBtn->SetBackgroundColor(FLinearColor::Gray);

			QuitToMain->SetBackgroundColor(FLinearColor::Blue);
			PlayHoverSound();
		}
	}
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ResumeBtn)
	{
		
		ResumeBtn->SetKeyboardFocus();

	}
}

UWidget* UPauseWidget::GetFirstFocusableWidget() const
{
	return ResumeBtn;
}

bool UPauseWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (ResumeBtn)
	{
		ResumeBtn->OnClicked.AddDynamic(this, &UPauseWidget::ResumeBtnClicked);
		ResumeBtn->OnHovered.AddDynamic(this, &UPauseWidget::PlayHoverSound);
	}
	if (QuitToMain)
	{
		QuitToMain->OnClicked.AddDynamic(this, &UPauseWidget::MainMenuBtnClicked);
		QuitToMain->OnHovered.AddDynamic(this, &UPauseWidget::PlayHoverSound);
	}

	return true;
}

void UPauseWidget::ResumeBtnClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
	{
		CubeController->RemovePauseMenu();
	}

}

void UPauseWidget::MainMenuBtnClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
	{
		CubeController->ChangeLevel("MainMenuMap");
	}
}

void UPauseWidget::EnableWidgetNavigation()
{
	UWidget* FirstWidget = GetFirstFocusableWidget();
	if (FirstWidget)
	{
		FirstWidget->SetKeyboardFocus();
		//FirstWidget->SetFocus();


	}
}

void UPauseWidget::PlayHoverSound()
{
	if (HoverSound)
	{

		UGameplayStatics::PlaySound2D(this, HoverSound);
	}
}
