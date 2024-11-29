// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "GameFramework/PlayerController.h"
#include "DeadWidget.h"
#include "PauseWidget.h"
#include "AfterDiedWidget.h"
#include "GoalWidget.h"
#include "ControllerWidget.h"
#include "ShowControlWidget.h"
#include "InformationWidget.h"

void APlayerHUD::DrawHUD()
{

}
void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	AddDieWid();
	AddPauseMenu();
	AddAfterDedWid();
	AddGoalWidget();
	AddControlWidget();
	AddShowControlWidget();
	AddInfolWidget();
}

void APlayerHUD::AddCharacterOverlay()
{

}
void APlayerHUD::AddDieWid()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && DeadWidgetclass)
	{
		DeadWidget = CreateWidget<UDeadWidget>(PlayerController, DeadWidgetclass);
		
	}
}

void APlayerHUD::AddPauseMenu()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && PauseGameClass) 
	{
		PauseMenuWidget = CreateWidget<UPauseWidget>(PlayerController, PauseGameClass);
	}
}

void APlayerHUD::AddAfterDedWid()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && AfterDiedClass)
	{
		AfterDiedWidget = CreateWidget<UAfterDiedWidget>(PlayerController, AfterDiedClass);
	}

}

void APlayerHUD::AddGoalWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && GoalWidClass)
	{
		GoalWidget = CreateWidget<UGoalWidget>(PlayerController, GoalWidClass);
	}

}

void APlayerHUD::AddControlWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && ControlWidClass)
	{
		ControlWidget = CreateWidget<UControllerWidget>(PlayerController, ControlWidClass);
	}
}

void APlayerHUD::AddShowControlWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && ShowControlWidClass)
	{
		ShowWidget = CreateWidget<UShowControlWidget>(PlayerController, ShowControlWidClass);
	}
}

void APlayerHUD::AddInfolWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && InfolWidClass)
	{
		InfoWidget = CreateWidget<UInformationWidget>(PlayerController, InfolWidClass);
	}
}


