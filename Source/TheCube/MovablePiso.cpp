// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePiso.h"

void AMovablePiso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewPosition = GetActorLocation() + (CurrentDirection * MovementSpeed * DeltaTime);

	// Verificar si estamos fuera del rango en X
	if (FMath::Abs(NewPosition.X - InitialPosition.X) > FMath::Abs(MovementRange.X))
	{
		// Cambiar la dirección en X
		CurrentDirection.X *= -1.0f;
	}

	// Verificar si estamos fuera del rango en Y
	if (FMath::Abs(NewPosition.Y - InitialPosition.Y) > FMath::Abs(MovementRange.Y))
	{
		// Cambiar la dirección en Y
		CurrentDirection.Y *= -1.0f;
	}
	SetActorLocation(NewPosition);
}

void AMovablePiso::BeginPlay()
{
	Super::BeginPlay();

	InitialPosition = GetActorLocation();
}
