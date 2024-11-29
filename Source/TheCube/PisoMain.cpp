// Fill out your copyright notice in the Description page of Project Settings.


#include "PisoMain.h"
#include "Engine/SkeletalMeshSocket.h"
#include "TheCubeCharacter.h"
#include "Components/BoxComponent.h"
// Sets default values
APisoMain::APisoMain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(Mesh);
	DetectionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
}

// Called when the game starts or when spawned
void APisoMain::BeginPlay()
{
	Super::BeginPlay();
	
	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &APisoMain::OnSphereOverlap);
	DetectionBox->OnComponentEndOverlap.AddDynamic(this, &APisoMain::OnSphereEndOverlap);
	SetColorState(ColorState);
}

void APisoMain::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		ATheCubeCharacter* Jugador = Cast<ATheCubeCharacter>(OtherActor);
		if (Jugador && Mesh) 
		{
			CheckForState(Jugador);
			//UE_LOG(LogTemp, Warning, TEXT("PEgamos();"));
		}
	}

}

void APisoMain::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Setear otra vez a overlap y volver a revisar
	if (OtherActor)
	{
		ATheCubeCharacter* Jugador = Cast<ATheCubeCharacter>(OtherActor);
		if (Jugador && Mesh)
		{
			
			//Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			//UE_LOG(LogTemp, Warning, TEXT("Reseteamos();"));
		}
	}
}


// Called every frame
void APisoMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APisoMain::SetColorState(EColorState NewState)
{
	ColorState = NewState;

	switch (ColorState)
	{
	case EColorState::EWS_Idle:
		break;
	case EColorState::EWS_FirstColor:
		if (FirstColor) 
		{
			Mesh->SetMaterial(0, FirstColor);
		
		}
		
		break;
	case EColorState::EWS_SecondColor:
		if (SecondColor)
		{
			Mesh->SetMaterial(0, SecondColor);

		}
		break;
	case EColorState::EWS_ThirdColor:
		if (ThirdColor)
		{
			Mesh->SetMaterial(0, ThirdColor);

		}
		break;
	case EColorState::EWS_ForthColor:
		if (ForthColor)
		{
			Mesh->SetMaterial(0, ForthColor);

		}
		break;
	case EColorState::EWS_MAXSTATE:
		break;
	default:
		break;
	}
}

void APisoMain::CheckForState(ATheCubeCharacter* Player)
{
	if (Mesh) 
	{
		if (Player->GetColorState() == ColorState)
		{
			Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		}
		else
		{
			Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		}
	}
	
}

