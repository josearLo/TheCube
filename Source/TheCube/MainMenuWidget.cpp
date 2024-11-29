// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "CubeController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LevelStreaming.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void UMainMenuWidget::MenuSetup()
{
	UWorld* World = GetWorld();
	if (World)
	{
		ControlPersonaje = Cast<ACubeController>(World->GetFirstPlayerController());

		if (ControlPersonaje)
		{

			FInputModeGameAndUI InputModeData;
			InputModeData.SetWidgetToFocus(this->TakeWidget()); // Ahora utilizando el widget actual.
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			//bIsFocusable = true;
			// Establecer el modo de entrada para juego y UI.
			ControlPersonaje->SetInputMode(InputModeData);
			ControlPersonaje->bShowMouseCursor = true;
			EnableWidgetNavigation();

			//this->SetKeyboardFocus();
			AddToViewport();

		}
	}
	if (this->HasKeyboardFocus())
	{
		UE_LOG(LogTemp, Warning, TEXT("El widget tiene el foco de entrada."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("El widget NO tiene el foco de entrada."));
	}
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

UWidget* UMainMenuWidget::GetFirstFocusableWidget() const
{
	return PlayGameBtn;
}

void UMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!PlayGameBtn->HasKeyboardFocus() && !QuitGameBtn->HasKeyboardFocus())
	{
		PlayGameBtn->SetKeyboardFocus();
	}
		
	if (PlayGameBtn && PlayGameBtn)
	{
		if (PlayGameBtn->HasKeyboardFocus() && !bAlreadyPlayGame )
		{
			bAlreadyPlayGame = true;
			bAlreadyQtBtn = false;
			PlayGameBtn->SetBackgroundColor(FLinearColor::Blue);
			
			QuitGameBtn->SetBackgroundColor(FLinearColor::Gray);
			PlayHoverSound();
			//UE_LOG(LogTemp, Warning, TEXT("PlayGameBtn"))
		}
		else if (QuitGameBtn->HasKeyboardFocus() && !bAlreadyQtBtn)
		{
			bAlreadyQtBtn = true;
			bAlreadyPlayGame = false;

			PlayGameBtn->SetBackgroundColor(FLinearColor::Gray);

			QuitGameBtn->SetBackgroundColor(FLinearColor::Blue);
			PlayHoverSound();
			//UE_LOG(LogTemp, Warning, TEXT("QuitGameBtn"))
		}
	}
}

bool UMainMenuWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (PlayGameBtn)
	{
		PlayGameBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGameClicked);
		PlayGameBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::PlayHoverSound);
		PlayGameBtn->SetBackgroundColor(FLinearColor::Gray);

	}
	if (QuitGameBtn) 
	{
		QuitGameBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGameClicked);
		QuitGameBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::PlayHoverSound);

		QuitGameBtn->SetBackgroundColor(FLinearColor::Gray);
	}

	return true;
}

void UMainMenuWidget::PlayGameClicked()
{
	PlayPressedSound();
	FName NivelACargar = "ThirdPersonMap";

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();



		if (PlayerController)
		{
			//FInputModeGameAndUI InputModeData;
			FInputModeGameOnly InputModeData;
			//InputModeData.SetWidgetToFocus(TakeWidget());
			//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}


	}


	UGameplayStatics::OpenLevel(GetWorld(), NivelACargar);
}

void UMainMenuWidget::QuitGameClicked()
{
	PlayPressedSound();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
}

void UMainMenuWidget::EnableWidgetNavigation()
{
	UWidget* FirstWidget = GetFirstFocusableWidget();
	if (FirstWidget)
	{
		FirstWidget->SetKeyboardFocus();
		//FirstWidget->SetFocus();


	}
}

void UMainMenuWidget::PlayHoverSound()
{
	if (HoverSound)
	{

		UGameplayStatics::PlaySound2D(this, HoverSound);
	}
}

void UMainMenuWidget::PlayPressedSound()
{
	if (PressedSound)
	{
		UGameplayStatics::PlaySound2D(this, PressedSound);
	}
}
