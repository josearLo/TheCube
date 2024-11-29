// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorChanger.generated.h"

UENUM(BlueprintType)
enum class EColorToChange : uint8
{
	ECC_Idle UMETA(DisplayName = "Initial State"),
	ECC_FirstColor UMETA(DisplayName = "FirstColor"),
	ECC_SecondColor UMETA(DisplayName = "SecondColor"),
	ECC_ThirdColor UMETA(DisplayName = "ThirdColor"),
	ECC_ForthColor UMETA(DisplayName = "ForthColor"),
	ECC_MAXSTATE UMETA(DisplayName = "DefaultMAX")
};



class UStaticMeshComponent;
class USphereComponent;
class ATheCubeCharacter;

UCLASS()
class THECUBE_API AColorChanger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorChanger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* SoundDestruction;

	UFUNCTION()
	void PlaySound(USoundBase* Sound, FVector Location);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	USphereComponent* AreaSphere;
	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	EColorToChange ColorToChange;
	void ChangeCubeColor(ATheCubeCharacter* Character);
	bool bSounded = false;

};
