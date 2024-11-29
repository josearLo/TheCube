// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CubeController.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API ACubeController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	//---Funciones con Widgets
	void SetDeadText();
	void SetDeadWidget();
	void RemoveDeadWidget();
	void SetPauseMenu();
	void RemovePauseMenu();
	void AddAfterDedWid();
	void RemoveAfterDedWid();
	void AddGoalWidget();
	void RemoveGoalWidget();

	void AddControlWidget();
	void RemoveControlWidget();

	void AddShowControlWidget();
	void RemoveShowControlWidget();

	void AddInfoWidget();
	void RemoveInfoWidget();

	void SetTextInfoWidget(FString NewText);
	//---------
	void ChangeLevel(const FString& LevelName);

	void LoadLevel();

	//----------
	//Usemos este bool para todos
	bool bGoalWidget = false;

private:
	UPROPERTY()
	class APlayerHUD* CharacterHUD;
	
};
