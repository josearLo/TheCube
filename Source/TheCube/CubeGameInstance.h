// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CubeGameInstance.generated.h"

class ATheCubeCharacter;
class USaveCubeGame;

UCLASS()
class THECUBE_API UCubeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	USaveCubeGame* GameData;
	UPROPERTY()
	FString SaveSlot = "GameData";
	void Init() override;
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	USaveCubeGame* LoadGameData();
	void SaveFirstMessage(bool Entry);
	void SaveLevelName(FString LName);
};
