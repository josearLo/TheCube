// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "Components/BoxComponent.h"
#include "TheCubeCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CubeController.h"
#include "GoalWidget.h"
// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(RootComponent);
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(DetectionBox);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	if (NiagaraComponent)
	{
		NiagaraComponent->Activate();
	}

	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnSphereOverlap);

}

void AGoal::PlaySound(USoundBase* Sound, FVector Location)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
	}
}

void AGoal::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Cube = Cast<ATheCubeCharacter>(OtherActor);
		if (Cube && bFinishLevel) 
		{
			Cube->SetPlayerState(EPlayerState::EPS_LevelPassed);
			Cube->bGoalReached = true;
			GetWorld()->GetTimerManager().SetTimer(NewLevelHandle, this, &AGoal::LoadNewLevel, 5.f, false);
			//Sonido
			PlaySound(FisnishedSound, GetActorLocation());
			DetectionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else if(Cube && !bFinishLevel && !bShowWid)
		{
			PlaySound(GoalSound, GetActorLocation());
			Destroy();
		}
		else if (Cube && !bFinishLevel && bShowWid) 
		{
			//Show widget
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (ACubeController* CubeController = Cast<ACubeController>(PlayerController)) 
			{
				CubeController->AddGoalWidget();
				CubeController->bGoalWidget = true;
				PlaySound(GoalSound, GetActorLocation());
				DetectionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Destroy();
			}
			
		}

	}
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::LoadNewLevel()
{
	if (GetWorld())
	{
		FName CurrentLevelName = *GetWorld()->GetName();
		if (CurrentLevelName == "ThirdPersonMap") 
		{
			CurrentLevelName = "SecondMap";
		}
		else if (CurrentLevelName == "SecondMap") 
		{
			CurrentLevelName = "ThirdMap";
		}
		else if (CurrentLevelName == "ThirdMap")
		{
			CurrentLevelName = "MainMenuMap";
						
		}
		
			UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
		
		
	}

}

