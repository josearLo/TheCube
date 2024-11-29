// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class ATheCubeCharacter;
class UPauseWidget;

UCLASS()
class THECUBE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	UPROPERTY()
	ATheCubeCharacter* Player;
	UPROPERTY()
	class UDeadWidget* DeadWidget;
	UPROPERTY()
	class UAfterDiedWidget* AfterDiedWidget;
	UPROPERTY()
	class UGoalWidget* GoalWidget;
	
	UPROPERTY()
	class UControllerWidget* ControlWidget;

	UPROPERTY()
	class UShowControlWidget* ShowWidget;
	UPROPERTY()
	class UInformationWidget* InfoWidget;

	UPROPERTY()
	UPauseWidget* PauseMenuWidget;//--Pause Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> DeadWidgetclass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> PauseGameClass;//--Pause Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> AfterDiedClass;//--AfterDied Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> GoalWidClass;//--GoalWid Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ShowControlWidClass;//--GoalWid Game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> InfolWidClass;//--GoalWid Game

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ControlWidClass;//--ControllerWid Game

	void AddDieWid();
	void AddPauseMenu();
	void AddAfterDedWid();
	void AddGoalWidget();
	void AddControlWidget();
	void AddShowControlWidget();
	void AddInfolWidget();
protected:
	virtual void BeginPlay() override;
	void AddCharacterOverlay();
};
