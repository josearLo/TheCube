// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeController.h"
#include "TheCubeCharacter.h"
#include "PlayerHUD.h"
#include "DeadWidget.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "PauseWidget.h"
#include "AfterDiedWidget.h"
#include "GoalWidget.h"
#include "ControllerWidget.h"
#include "ShowControlWidget.h"
#include "InformationWidget.h"

void ACubeController::BeginPlay()
{
	Super::BeginPlay();

	CharacterHUD = Cast<APlayerHUD>(GetHUD());
}

void ACubeController::SetDeadText()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;

	bool bHUDValidPause = CharacterHUD && CharacterHUD->DeadWidget && CharacterHUD->DeadWidget && CharacterHUD->DeadWidget->DeadText;
	if (bHUDValidPause)
	{
		CharacterHUD->DeadWidget->RandomTextList = { TEXT("LOL"), TEXT("Did you Die?"), TEXT("YOU DIED") };

		if (CharacterHUD->DeadWidget->RandomTextList.Num() > 0)
		{

			int32 RandomIndex = FMath::RandRange(0, CharacterHUD->DeadWidget->RandomTextList.Num() - 1);
			FString SelectedText = CharacterHUD->DeadWidget->RandomTextList[RandomIndex];
			CharacterHUD->DeadWidget->DeadText->SetText(FText::FromString(SelectedText));
		}
	}

}

void ACubeController::SetDeadWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;

	bool bHUDValidPause = CharacterHUD && CharacterHUD->DeadWidget && CharacterHUD->DeadWidget;
	if (bHUDValidPause)
	{

		CharacterHUD->DeadWidget->AddToViewport();
		SetDeadText();
		if (CharacterHUD->DeadWidget->Animation)
		{
			CharacterHUD->DeadWidget->PlayAnimation(CharacterHUD->DeadWidget->Animation);
		}

	}
}

void ACubeController::RemoveDeadWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->DeadWidget && CharacterHUD->DeadWidget;
	if (bHUDValidPause)
	{
		CharacterHUD->DeadWidget->RemoveFromParent();
		
	}
}

void ACubeController::SetPauseMenu()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->PauseGameClass && CharacterHUD->PauseMenuWidget;
	if (bHUDValidPause)
	{
		bShowMouseCursor = true;

		//SetInputMode(FInputModeGameAndUI());
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(CharacterHUD->PauseMenuWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		CharacterHUD->PauseMenuWidget->EnableWidgetNavigation();
		CharacterHUD->PauseMenuWidget->AddToViewport();
	}
}

void ACubeController::RemovePauseMenu()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;

	bool bHUDValidPause = CharacterHUD && CharacterHUD->PauseGameClass && CharacterHUD->PauseMenuWidget;
	if (bHUDValidPause)
	{
		bShowMouseCursor = false;
		CharacterHUD->PauseMenuWidget->RemoveFromParent(); //
		SetInputMode(FInputModeGameOnly());
		SetPause(false);
	}
}

void ACubeController::AddAfterDedWid()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->AfterDiedClass && CharacterHUD->AfterDiedWidget;
	if (bHUDValidPause)
	{
		bShowMouseCursor = true;

		//SetInputMode(FInputModeGameAndUI());
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(CharacterHUD->AfterDiedWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		CharacterHUD->AfterDiedWidget->EnableWidgetNavigation();
		CharacterHUD->AfterDiedWidget->AddToViewport();
	}
}

void ACubeController::RemoveAfterDedWid()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->AfterDiedClass && CharacterHUD->AfterDiedWidget;
	if (bHUDValidPause)
	{
		bShowMouseCursor = false;
		CharacterHUD->PauseMenuWidget->RemoveFromParent(); //
		SetInputMode(FInputModeGameOnly());
	}
}

void ACubeController::AddGoalWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->GoalWidClass && CharacterHUD->GoalWidget;
	if (bHUDValidPause) 
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(CharacterHUD->GoalWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		CharacterHUD->GoalWidget->EnableWidgetNavigation();
		CharacterHUD->GoalWidget->AddToViewport();
	}
}

void ACubeController::RemoveGoalWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->GoalWidClass && CharacterHUD->GoalWidget;
	if (bHUDValidPause)
	{
		bShowMouseCursor = false;
		CharacterHUD->GoalWidget->RemoveFromParent(); //
		SetInputMode(FInputModeGameOnly());
	}
}


void ACubeController::ChangeLevel(const FString& LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}

void ACubeController::LoadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}

void ACubeController::AddControlWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->ControlWidClass && CharacterHUD->ControlWidget;

	if (bHUDValidPause) 
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(CharacterHUD->ControlWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		CharacterHUD->ControlWidget->EnableWidgetNavigation();
		CharacterHUD->ControlWidget->AddToViewport();
		bGoalWidget = true;
	}
}

void ACubeController::RemoveControlWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->ControlWidClass && CharacterHUD->ControlWidget;

	if (bHUDValidPause) 
	{
		bShowMouseCursor = false;
		CharacterHUD->ControlWidget->RemoveFromParent(); //
		SetInputMode(FInputModeGameOnly());
	}
}

void ACubeController::AddShowControlWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->ShowControlWidClass && CharacterHUD->ShowWidget;

	if (bHUDValidPause) 
	{
		CharacterHUD->ShowWidget->AddToViewport();
	}
}

void ACubeController::RemoveShowControlWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->ShowControlWidClass && CharacterHUD->ShowWidget;

	if (bHUDValidPause)
	{
		CharacterHUD->ShowWidget->RemoveFromParent();
	}
}

void ACubeController::AddInfoWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->InfolWidClass && CharacterHUD->InfoWidget;

	if (bHUDValidPause) 
	{
		bGoalWidget = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(CharacterHUD->InfoWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		CharacterHUD->InfoWidget->EnableWidgetNavigation();
		
		CharacterHUD->InfoWidget->AddToViewport();
	}
}

void ACubeController::RemoveInfoWidget()
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->InfolWidClass && CharacterHUD->InfoWidget;
	if (bHUDValidPause)
	{
		bGoalWidget = false;
	bShowMouseCursor = false;
	CharacterHUD->InfoWidget->RemoveFromParent(); //
	SetInputMode(FInputModeGameOnly());
	}
}

void ACubeController::SetTextInfoWidget(FString NewText)
{
	CharacterHUD = CharacterHUD == nullptr ? Cast<APlayerHUD>(GetHUD()) : CharacterHUD;
	bool bHUDValidPause = CharacterHUD && CharacterHUD->InfolWidClass && CharacterHUD->InfoWidget && CharacterHUD->InfoWidget->TxtInfo;
	if (bHUDValidPause) 
	{
		FString SelectedText = NewText;
		CharacterHUD->InfoWidget->TxtInfo->SetText(FText::FromString(SelectedText));
	}
}