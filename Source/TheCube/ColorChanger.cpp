// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorChanger.h"
#include "Components/SphereComponent.h"
#include "TheCubeCharacter.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>

AColorChanger::AColorChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	AreaSphere->SetupAttachment(RootComponent);

	ColorToChange = EColorToChange::ECC_Idle;
}

void AColorChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorChanger::PlaySound(USoundBase* Sound, FVector Location)
{
	if (Sound && !bSounded)
	{

		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
		bSounded = true;
	}
}

void AColorChanger::BeginPlay()
{
	Super::BeginPlay();

	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AColorChanger::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AColorChanger::OnSphereEndOverlap);
	
}

void AColorChanger::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Cube = Cast<ATheCubeCharacter>(OtherActor);

		if (Cube) 
		{

			ChangeCubeColor(Cube);
			PlaySound(SoundDestruction, GetActorLocation());

		}
	
	}

}

void AColorChanger::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Cube = Cast<ATheCubeCharacter>(OtherActor);

		if (Cube) 
		{
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	
	}
}




void AColorChanger::ChangeCubeColor(ATheCubeCharacter* Character)
{
	switch (ColorToChange)
	{
	case EColorToChange::ECC_FirstColor:
		Character->SetColorState(EColorState::EWS_FirstColor);
		break;
	case EColorToChange::ECC_SecondColor:
		Character->SetColorState(EColorState::EWS_SecondColor);
		break;
	case EColorToChange::ECC_ThirdColor:
		Character->SetColorState(EColorState::EWS_ThirdColor);
		break;
	case EColorToChange::ECC_ForthColor:
		Character->SetColorState(EColorState::EWS_ForthColor);
		break;
	default:
		// Puedes manejar el caso por defecto si es necesario
		break;
	}
}

