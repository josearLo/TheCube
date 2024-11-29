// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterDiedWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "CubeController.h"


void UAfterDiedWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UAfterDiedWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ResumeBtn)
	{

		ResumeBtn->SetKeyboardFocus();

	}
}

UWidget* UAfterDiedWidget::GetFirstFocusableWidget() const
{
	return ResumeBtn;
}

bool UAfterDiedWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (ResumeBtn)
	{
		ResumeBtn->OnClicked.AddDynamic(this, &UAfterDiedWidget::PlayGameClicked);
		ResumeBtn->OnHovered.AddDynamic(this, &UAfterDiedWidget::PlayHoverSound);
		ResumeBtn->SetBackgroundColor(FLinearColor::Gray);

	}
	if (QuitToMain)
	{
		QuitToMain->OnClicked.AddDynamic(this, &UAfterDiedWidget::QuitGameClicked);
		QuitToMain->OnHovered.AddDynamic(this, &UAfterDiedWidget::PlayHoverSound);

		QuitToMain->SetBackgroundColor(FLinearColor::Gray);
	}

	return true;
}

void UAfterDiedWidget::PlayGameClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
	{
		if (GetWorld())
		{
			CubeController->RemoveAfterDedWid();
			FName CurrentLevelName = *GetWorld()->GetName();
			UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
			
		}
	}

	
	

}

void UAfterDiedWidget::QuitGameClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
	{
		//CubeController->RemoveAfterDedWid();
		if (GetWorld())
		{
			FName CurrentLevelName = "MainMenuMap";
			UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
		}
	}
}

void UAfterDiedWidget::EnableWidgetNavigation()
{
	UWidget* FirstWidget = GetFirstFocusableWidget();
	if (FirstWidget)
	{
		FirstWidget->SetKeyboardFocus();
		
	}
}

void UAfterDiedWidget::PlayHoverSound()
{
	if (HoverSound)
	{

		UGameplayStatics::PlaySound2D(this, HoverSound);
	}
}
