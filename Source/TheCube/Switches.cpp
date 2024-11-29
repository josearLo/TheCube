// Fill out your copyright notice in the Description page of Project Settings.


#include "Switches.h"
#include "TheCubeCharacter.h"
#include "PisoMain.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASwitches::ASwitches()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ASwitches::BeginPlay()
{
	Super::BeginPlay();
	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &ASwitches::OnSphereOverlap);
}

void ASwitches::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Player = Cast<ATheCubeCharacter>(OtherActor);
		if (Player) 
		{
			if (Piso) 
			{
				PlaySound(SoundDestruction, GetActorLocation());
				Piso->SetColorState(ColorStatePiso);
				DetectionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				UE_LOG(LogTemp, Warning, TEXT("NO COLLISION"));
			}
		
		}
	}
}

// Called every frame
void ASwitches::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitches::PlaySound(USoundBase* Sound, FVector Location)
{
	if (Sound && !bSounded)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
		bSounded = true;
	}
}

