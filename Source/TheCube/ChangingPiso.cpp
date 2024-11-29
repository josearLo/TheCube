// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangingPiso.h"
#include "TheCubeCharacter.h"


void AChangingPiso::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ColorChangerHandle, this, &AChangingPiso::ChangeColorSequence, ChangeTime, true);
    //ColorState = EColorState::EWS_FirstColor;
    if (GetWorld()) 
    {
        Cube = Cast <ATheCubeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    }
  
}

void AChangingPiso::ChangeColorSequence()
{
    // Array con los colores y sus estados correspondientes
    TArray<UMaterialInterface*> Colors = { FirstColor, SecondColor, ThirdColor, ForthColor };
    TArray<EColorState> ColorStates = {
        EColorState::EWS_FirstColor,
        EColorState::EWS_SecondColor,
        EColorState::EWS_ThirdColor,
        EColorState::EWS_ForthColor
    };
    
    // Verificar que el índice sea válido y que existan colores
    if (Mesh && Colors.IsValidIndex(ColorIndex) && ColorStates.IsValidIndex(ColorIndex))
    {
        // Cambiar el material
        Mesh->SetMaterial(0, Colors[ColorIndex]);

        // Actualizar el estado
        ColorState = ColorStates[ColorIndex];

        if (Cube) 
        {
            CheckForState(Cube);
        }
        // Depuración
        //
        // UE_LOG(LogTemp, Warning, TEXT("Cambiando al color: %d, Estado: %d"), ColorIndex, static_cast<int32>(ColorState));

        // Incrementar el índice y reiniciarlo si llega al final
        ColorIndex = (ColorIndex + 1) % Colors.Num();
    }
	
}
