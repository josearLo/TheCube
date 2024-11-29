// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PisoMain.h"
#include "ChangingPiso.generated.h"

class UMaterialInterface;
class ATheCubeCharacter;

UCLASS()
class THECUBE_API AChangingPiso : public APisoMain
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* FirstColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* SecondColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ThirdColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ForthColor;*/

	FTimerHandle ColorChangerHandle;
	void ChangeColorSequence();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	float ChangeTime = 3.f;
	int32 ColorIndex = 0; // Índice actual del color
	bool bChangeFirst = false;
	bool bChangeSecond = false;
	bool bChangeThird = false;
	bool bChangeForth = false;
	UPROPERTY()
	ATheCubeCharacter* Cube;
};
