// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PisoMain.h"
#include "MovablePiso.generated.h"

/**
 * 
 */
UCLASS()
class THECUBE_API AMovablePiso : public APisoMain
{
	GENERATED_BODY()
	
protected:

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementRange = FVector(500.0f, 0.0f, 0.0f);;

	// Velocidad de movimiento
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 200.f;

	// Dirección del movimiento
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector CurrentDirection = FVector(1.0f, 0.0f, 0.0f);

	// Posición inicial
	FVector InitialPosition;
};
