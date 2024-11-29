// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheCubeCharacter.h"
#include "PisoMain.generated.h"

class ATheCubeCharacter;
class UBoxComponent;

UCLASS()
class THECUBE_API APisoMain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APisoMain();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	EColorState ColorState;
	void SetColorState(EColorState NewState);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void CheckForState(ATheCubeCharacter* Player); //Este va en el tick para detectar que el jugador este del mismo estado
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* FirstColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* SecondColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ThirdColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ForthColor;
private:
	
	
	UPROPERTY(EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DetectionBox;
	
	
	

};
