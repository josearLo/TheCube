// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableDoors.h"
#include "TheCubeCharacter.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABreakableDoors::ABreakableDoors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(Mesh);

	DissolveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DissolveTimelineComponent"));
}

// Called when the game starts or when spawned
void ABreakableDoors::BeginPlay()
{
	Super::BeginPlay();
	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &ABreakableDoors::OnSphereOverlap);
	DetectionBox->OnComponentEndOverlap.AddDynamic(this, &ABreakableDoors::OnSphereEndOverlap);
}

void ABreakableDoors::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ATheCubeCharacter* Cube2 = Cast<ATheCubeCharacter>(OtherActor);

		if (Cube2)
		{
			Cube = nullptr;
		}

	}
}

void ABreakableDoors::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Cube2 = Cast<ATheCubeCharacter>(OtherActor);

		if (Cube2 )
		{
			Cube = Cube2;
		}

	}

}

void ABreakableDoors::PlaySound(USoundBase* Sound, FVector Location)
{
	if (Sound && !bSounded)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
		bSounded = true;
	}
}


void ABreakableDoors::CheckToDestroyWall() 
{
	if (Cube && Cube->GetbImpulsed()) 
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayDissolve();
		GetWorld()->GetTimerManager().SetTimer(DestroyWallTimer, this, &ABreakableDoors::DestroyWall, 4.f, false);
		//La destruccion va a ser con el efecto aquel de los chopos y se destruye
		PlaySound(SoundDestruction, GetActorLocation());
	
	}
}

void ABreakableDoors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckToDestroyWall();
}

void ABreakableDoors::UpdateDissolveMaterial(float DissolveValue)
{
	if (DynamicDissolveMaterialInstance)
	{
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dessolve"), DissolveValue);
	}
}

void ABreakableDoors::StartDissolve()
{
	DissolveTrack.BindDynamic(this, &ABreakableDoors::UpdateDissolveMaterial);
	if (DissolveCurve && DissolveTimeline)
	{
		DissolveTimeline->AddInterpFloat(DissolveCurve, DissolveTrack);
		DissolveTimeline->Play();
	}
}

void ABreakableDoors::PlayDissolve()
{
	if (DissolveMaterialInstance)
	{
		DynamicDissolveMaterialInstance = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		Mesh->SetMaterial(0, DynamicDissolveMaterialInstance);
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Dessolve"), 0.55f);
		DynamicDissolveMaterialInstance->SetScalarParameterValue(TEXT("Glow"), 400.f);
	}
	StartDissolve();
}

void ABreakableDoors::DestroyWall()
{
	Destroy();

}
