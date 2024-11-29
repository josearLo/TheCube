// Fill out your copyright notice in the Description page of Project Settings.


#include "InformationActor.h"
#include "TheCubeCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AInformationActor::AInformationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(RootComponent);
	
	
	DetectionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AInformationActor::BeginPlay()
{
	Super::BeginPlay();
	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &AInformationActor::OnSphereOverlap);
}

void AInformationActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Jugador = Cast<ATheCubeCharacter>(OtherActor);

		if (Jugador) 
		{
			balreadydisplayed = true;
			Jugador->SetTextInfo(MessageOne);
			Jugador->AddInfoWidget();
			DetectionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

// Called every frame
void AInformationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

