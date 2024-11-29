// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveCubeGame.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API USaveCubeGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector PlayerLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString LevelName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bShowFirstMessage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bShowActorMessage;

};
