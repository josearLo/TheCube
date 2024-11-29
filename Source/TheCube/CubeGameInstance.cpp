// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGameInstance.h"
#include "SaveCubeGame.h"
#include "TheCubeCharacter.h"
#include "Kismet/GameplayStatics.h"

void UCubeGameInstance::Init()
{
	Super::Init();
	// check if there is game data to load it
	// or create a new one if the game is just starting
	GameData = Cast<USaveCubeGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));

	if (!GameData)
	{
		// Si no hay datos guardados, crea una nueva instancia
		GameData = Cast<USaveCubeGame>(UGameplayStatics::CreateSaveGameObject(USaveCubeGame::StaticClass()));

		if (GameData)
		{
			// iniciarlizar los datos del juego con valores por defecto

			GameData->PlayerLocation = FVector(0,0,0);
			GameData->LevelName = "ThirdPersonMap";
			GameData->bShowActorMessage = false;
			GameData->bShowFirstMessage = false;

			// Guarda la nueva instancia en el slot
			if (UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0))
			{
				UE_LOG(LogTemp, Warning, TEXT("New game data created and saved successfully"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to save new game data to slot"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create new GameData instance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game data loaded from slot successfully"));
	}
}

USaveCubeGame* UCubeGameInstance::LoadGameData()
{
	if (!GameData)
	{
		GameData = Cast<USaveCubeGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));

		if (!GameData)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load game data from slot: %s"), *SaveSlot);
			return nullptr;
		}

		UE_LOG(LogTemp, Warning, TEXT("Game data loaded successfully from slot: %s"), *SaveSlot);
	}

	return GameData;
}

void UCubeGameInstance::SaveFirstMessage(bool Entry)
{
	if (!GameData)return;
	GameData->bShowFirstMessage = Entry;
	UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
}

void UCubeGameInstance::SaveLevelName(FString LName)
{
	if (!GameData)return;
	GameData->LevelName = LName;
	UGameplayStatics::SaveGameToSlot(GameData, SaveSlot, 0);
}
