// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

class UNiagaraSystem;
class UBoxComponent;
class USoundBase;
class UNiagaraComponent;
UCLASS()
class THECUBE_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bNotLevelLoad = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NiagaraComponent;
	UPROPERTY(EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DetectionBox;
	FTimerHandle NewLevelHandle;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* GoalSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* FisnishedSound;
	UPROPERTY(EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	bool bFinishLevel = false;
	UPROPERTY(EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	bool bShowWid = false;
	void LoadNewLevel();
	UFUNCTION()
	void PlaySound(USoundBase* Sound, FVector Location);

	
};
