// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheCubeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CubeController.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>
#include "CubeGameInstance.h"
#include "SaveCubeGame.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATheCubeCharacter

ATheCubeCharacter::ATheCubeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)ColorState
	//ColorState = EColorState::EWS_FirstColor;
	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CAPMesh"));
	CapMesh->SetupAttachment(GetMesh());

	NiagaraDashEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DashEffect"));
	NiagaraDashEffect->SetupAttachment(GetMesh());

}

void ATheCubeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (NiagaraDashEffect) 
	{
		//NiagaraDashEffect->SetAutoActivate(false);
		NiagaraDashEffect->DeactivateImmediate();
		NiagaraDashEffect->Deactivate();
	}
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(PlaneNormal);
	SetColorState(EColorState::EWS_FirstColor);
	StateOfThePlayer = EPlayerState::EPS_Alive;
	PlaySound(MotorSound,GetActorLocation());
	bGoalReached = false;
	//AddControlWid();
	//----Game Instance

	MyGameInstance = Cast<UCubeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance) 
	{
	//	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance"));
		GetWorld()->GetTimerManager().SetTimer(SaveFirstMessageTimer, this, &ATheCubeCharacter::AddControlWid, 0.2f, false); //SaveFirstMessage
	
	}
	
	//LoadCurrentLevel();
}

void ATheCubeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckWall();
}

void ATheCubeCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	//Meter toda la logica que vamos hacer aca
	if (!bAlreadyDead) 
	{
		bAlreadyDead = true;
		SetPlayerState(EPlayerState::EPS_Dead);
	}
	
	
}

void ATheCubeCharacter::ShowControlStarted()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;

	if (ControllerCube) 
	{
		ControllerCube->AddShowControlWidget();
	}
}

void ATheCubeCharacter::ShowControlCompleted()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;

	if (ControllerCube) 
	{
		ControllerCube->RemoveShowControlWidget();
	}
}

void ATheCubeCharacter::PauseGame()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;

	if (ControllerCube) 
	{
		ControllerCube->SetPause(true);
		//UE_LOG(LogTemp, Warning, TEXT("Pause Game true:"));

		ControllerCube->SetPauseMenu();
	}
}

void ATheCubeCharacter::ZoomCamera(const FInputActionValue& ValueZ)
{
	float AxisValue = ValueZ.Get<float>();

	// Modificar la longitud del SpringArm según el valor del eje de la rueda del mouse y la velocidad de zoom
	float NewTargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength - (AxisValue * ZoomSpeed), MinZoom, MaxZoom);

	CameraBoom->TargetArmLength = NewTargetArmLength;

	// Log para verificar la distancia del zoom
	UE_LOG(LogTemp, Warning, TEXT("Zoom cambiado: %f"), NewTargetArmLength);
}


//////////////////////////////////////////////////////////////////////////
// Input

void ATheCubeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATheCubeCharacter::DoubleJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATheCubeCharacter::Move);

		// Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATheCubeCharacter::Look);

		EnhancedInputComponent->BindAction(ImpulseFrontAction, ETriggerEvent::Started, this, &ATheCubeCharacter::AddImpulse);

		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Started, this, &ATheCubeCharacter::RotateClockwise);

		EnhancedInputComponent->BindAction(RotateOpositeAction, ETriggerEvent::Started, this, &ATheCubeCharacter::RotateCounterClockwise);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ATheCubeCharacter::PauseGame);

		EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Started, this, &ATheCubeCharacter::ZoomCamera);

		EnhancedInputComponent->BindAction(ShowControlAction, ETriggerEvent::Started, this, &ATheCubeCharacter::ShowControlStarted);
		EnhancedInputComponent->BindAction(ShowControlAction, ETriggerEvent::Completed, this, &ATheCubeCharacter::ShowControlCompleted);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATheCubeCharacter::Move(const FInputActionValue& Value)
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube->bGoalWidget)return; //Si tenemos el widget en el mundo no hacemos nada hasta cerrar
	if (bGoalReached)return;
	if (bIsRotating) return;
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		

		FRotator CameraRotation = CameraBoom->GetRelativeRotation();

		
		FVector RightDirection = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::Y);

		
		AddMovementInput(RightDirection, MovementVector.X);
		PlaySound(AccelerateSound, GetActorLocation());
	}
}

void ATheCubeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATheCubeCharacter::AddImpulse()
{
	if (StateOfThePlayer == EPlayerState::EPS_LevelPassed)return; //No dash after die
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube->bGoalWidget)return; //Si tenemos el widget en el mundo no hacemos nada hasta cerrar

	if (StateOfThePlayer == EPlayerState::EPS_Dead)return; //No dash after die
	if (!bImpulsed) 
	{
		bImpulsed = true;
		/*FVector ForwardVelocity = GetActorForwardVector();
		ForwardVelocity.Normalize();
		FVector ImpulseJumpFor = ForwardVelocity * SaltoAdelante + SaltoDash;
		LaunchCharacter(ImpulseJumpFor, true, true);*/
		GetCharacterMovement()->MaxWalkSpeed = DashSpeed;
		EffectOnDash();
		PlaySound(DashSound, GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(AddImpulseTimer, this, &ATheCubeCharacter::ResetbImpulse, 2.f, false);
	}
	
}

void ATheCubeCharacter::ResetbImpulse()
{
	bImpulsed = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	if (NiagaraDashEffect)
	{
		NiagaraDashEffect->DeactivateImmediate();
	}
}



void ATheCubeCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	PlaySound(LandedSound, GetActorLocation());
	bWearejumping = false;
	TheresAWall = false;
	ConteoDelSalto = 0;
	PlayCamaraShake();
}

void ATheCubeCharacter::RotateWorld(float RotationAmount)
{
	
	if (bIsRotating) return; // Evitar que se inicie otra rotación mientras una está en progreso

	StartRotation = CameraBoom->GetRelativeRotation();
	TargetRotation = StartRotation;
	TargetRotation.Yaw += RotationAmount;

	// Normaliza el ángulo a un rango entre 0 y 360
	TargetRotation.Yaw = FMath::Fmod(TargetRotation.Yaw, 360.0f);
	if (TargetRotation.Yaw < 0)
	{
		TargetRotation.Yaw += 360.0f;
	}

	// Activar la rotación
	bIsRotating = true;

	// Configura el temporizador para rotar la cámara gradualmente
	GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, this, &ATheCubeCharacter::UpdateRotation, 0.01f, true);

}

void ATheCubeCharacter::RotateClockwise(const FInputActionValue& RoTa)
{
	if (GetCharacterMovement()->IsFalling() || bWearejumping)return;
	RotateWorld(-90.0f);
}

void ATheCubeCharacter::RotateCounterClockwise(const FInputActionValue& RoTe)
{
	if (GetCharacterMovement()->IsFalling() || bWearejumping)return; //No se rota camara durante salto o caida de personaje
	RotateWorld(90.0f);
}

void ATheCubeCharacter::EffectOnDash()
{

	//Niagara effect aqio
	if (NiagaraDashEffect)
	{
		//// Obtén la orientación actual del personaje
		//FVector ActorForward = GetActorForwardVector(); // Vector que apunta hacia el frente del personaje
		//FVector ActorLocation = GetActorLocation();

		//// Calcula la ubicación detrás del personaje
		// OffsetDistance = 100.0f; // Ajusta este valor para determinar cuán lejos detrás del personaje aparece el efecto OffsetDistance
		//FVector SpawnLocation = ActorLocation - (ActorForward * OffsetDistance);

		//// Asegúrate de que el efecto esté orientado hacia la dirección contraria al frente del personaje
		//FRotator EffectRotation = ActorForward.Rotation();
		//EffectRotation.Yaw += 180.0f; // Rota el efecto 180 grados para que "mire hacia atrás"
		////UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraDashEffect, ActorLocation, EffectRotation);
		NiagaraDashEffect->Activate();
	}
}



void ATheCubeCharacter::UpdateRotation()
{
	if (!bIsRotating) return;

	// Calcular la nueva rotación interpolada
	FRotator CurrentRotation = CameraBoom->GetRelativeRotation();
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);

	CameraBoom->SetRelativeRotation(NewRotation);

	// Verificar si alcanzamos la rotación objetivo
	if (NewRotation.Equals(TargetRotation, 1.0f))
	{
		// Detener la rotación
		bIsRotating = false;
		GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);

		// Ajustar `TargetRotation` a un valor exacto para evitar acumulación
		float ExactYaw = FMath::RoundToFloat(TargetRotation.Yaw / 90.0f) * 90.0f;
		TargetRotation.Yaw = ExactYaw;
		CameraBoom->SetRelativeRotation(FRotator(TargetRotation.Pitch, ExactYaw, TargetRotation.Roll));

		// Configurar el plano de movimiento con el valor redondeado de Yaw
		if (ExactYaw == 0.0f)
		{
			GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
		}
		else if (ExactYaw == 90.0f)
		{
			GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
		}
		else if (ExactYaw == 180.0f)
		{
			GetCharacterMovement()->SetPlaneConstraintNormal(FVector(-1.0f, 0.0f, 0.0f));
		}
		else if (ExactYaw == 270.0f)
		{
			GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));
		}
		else
		{
			GetCharacterMovement()->SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
			//UE_LOG(LogTemp, Warning, TEXT("Este caso no debería ocurrir();"));
		}
	}
}

void ATheCubeCharacter::SetColorState(EColorState State)
{
	ColorState = State;
	switch (ColorState)
	{
	case EColorState::EWS_Idle:
		break;
	case EColorState::EWS_FirstColor:
		if (FirstColor) 
		{
			GetMesh()->SetMaterial(0, FirstColor);
		}
		break;
	case EColorState::EWS_SecondColor:

		if (SecondColor)
		{
			GetMesh()->SetMaterial(0, SecondColor);
		}

		break;
	case EColorState::EWS_ThirdColor:

		if (ThirdColor)
		{
			GetMesh()->SetMaterial(0, ThirdColor);
		}

		break;
	case EColorState::EWS_ForthColor:
		
		if (ForthColor)
		{
			GetMesh()->SetMaterial(0, ForthColor);
		}

		break;
	case EColorState::EWS_MAXSTATE:
		break;
	default:
		break;
	}
}

void ATheCubeCharacter::CheckWall()
{
	if (GetCharacterMovement()->IsFalling()) 
	{
		FHitResult HitResult;
		FVector StartLocation = GetActorLocation();
		FVector EndLocation = StartLocation + (GetActorForwardVector() * 50.0f);  // Extiende el rayo 1000 unidades hacia adelante.
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);  // Ignora este actor al realizar el trazado.
	
		// Especificar el TraceChannel personalizado "WallJump"
		CollisionParams.TraceTag = FName("WallJump");

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

		if (bHit && HitResult.GetActor()->ActorHasTag("WallJump")) 
		{			
			//Entramos aqui si tocamos con una pared
			float DeltaSeconds = GetWorld()->GetDeltaSeconds();
			//DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Green, false, 2.f, 0, 2.f);
			FVector TargetLocation = FVector::ZeroVector;
			FVector TargetDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();
			FVector CurrentVelocity = GetCharacterMovement()->Velocity;

			FVector NewVelocity = FMath::VInterpConstantTo(CurrentVelocity, TargetDirection, DeltaSeconds, InterpSpeedWall);
			GetCharacterMovement()->Velocity = NewVelocity;
			//Niagara effect aqio
			if (NiagaraEffectWall)
			{
				FVector SpawnLocation = HitResult.Location + FVector(0.0f, 0.0f, OffSetEffectWall);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffectWall, SpawnLocation, FRotator::ZeroRotator);

			}
			//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2.f, 0, 2.f);
			
			TheresAWall = true; //Esto va afuera del niagara 
		}
		else
		{
			//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 2.f, 0, 2.f);
			TheresAWall = false;
		}
		 
		GravityWall(TheresAWall);
	}

}

void ATheCubeCharacter::GravityWall(bool IsThereAWall)
{
	if (TheresAWall) 
	{
		ConteoDelSalto = 0;
		//if (NiagaraComponent) //Desactivamos el Niagara al inicio

	}
	else 
	{
		
	}

}

void ATheCubeCharacter::AddDeadWidget()
{
	if (StateOfThePlayer == EPlayerState::EPS_LevelPassed)return; //No widget if alreadypassed
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;

	if (ControllerCube) 
	{
		ControllerCube->SetDeadWidget();
	}
}

void ATheCubeCharacter::RemoveDeadWidget()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;

	if (ControllerCube)
	{
		ControllerCube->RemoveDeadWidget();
	}
}

void ATheCubeCharacter::AddAfterDieWid()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube) 
	{
		ControllerCube->AddAfterDedWid();
	}
}



void ATheCubeCharacter::SetPlayerState(EPlayerState State)
{
	StateOfThePlayer = State;

	switch (StateOfThePlayer)
	{
	case EPlayerState::EPS_Alive:

		break;
	case EPlayerState::EPS_Dead:
		PlaySound(DeadSound, GetActorLocation());
		AddDeadWidget();
		SaveCurrentLevel();
		GetWorld()->GetTimerManager().SetTimer(ShowWidDedHandle, this, &ATheCubeCharacter::AddAfterDieWid, 4.f, false);
		//AddAfterDieWid();
		break;
	case EPlayerState::EPS_MAXSTATE:
		break;
	default:
		break;
	}
}



void ATheCubeCharacter::SetTextInfo(FString TextInfo)
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube)
	{
		 
		ControllerCube->SetTextInfoWidget(TextInfo);
	}
}

void ATheCubeCharacter::AddInfoWidget()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube) 
	{
		
		ControllerCube->AddInfoWidget();
	}
}



void ATheCubeCharacter::PlaySound(USoundBase* Sound, FVector Location)
{
	if (Sound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
	}
}

void ATheCubeCharacter::DoubleJump()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube->bGoalWidget)return; //Si tenemos el widget en el mundo no hacemos nada hasta cerrar
	if (StateOfThePlayer == EPlayerState::EPS_LevelPassed)return; //No dash after die
	if (TheresAWall) 
	{
		FVector ForwardVelocity = GetActorForwardVector() * ForwardPush;
		FVector Zvariable = FVector(0.0f, 0.0f, 1000.0f);
		FVector ImpulseJump = ForwardVelocity + Zvariable;
		//ConteoDelSalto++; //Probemos este
		PlaySound(JUmpSound, GetActorLocation());
		LaunchCharacter(ImpulseJump, true, true); //Podriamos probar con false y true
	}
	else 
	{
		ACharacter::Jump();
		if (!GetCharacterMovement()->IsFalling()) 
		{
			PlaySound(JUmpSound, GetActorLocation());
		}
		
		bWearejumping = true;
		ConteoDelSalto++;
		if (ConteoDelSalto == 2 && GetCharacterMovement()->IsFalling())
		{
		LaunchForward();
		PlaySound(JUmpDoubleSound, GetActorLocation());
		}
	
	}
	
}

void ATheCubeCharacter::LaunchForward()
{
	FVector ForwardVelocity = GetActorForwardVector();
	ForwardVelocity.Normalize();

	FVector UpwardVelocity = FVector::UpVector * SaltoVertical; // SaltoVertical es la cantidad de impulso hacia arriba deseado
	// Calcular el impulso final combinando el impulso hacia adelante y hacia arriba
	FVector ImpulseJumpFor = ForwardVelocity * SaltoAdelante + UpwardVelocity;
	LaunchCharacter(ImpulseJumpFor, true, true); //
}

void ATheCubeCharacter::SaveCurrentLevel()
{
	if (MyGameInstance)
	{
		FString Level = *GetWorld()->GetName();
		MyGameInstance->SaveLevelName(Level);
		UE_LOG(LogTemp, Warning, TEXT("SAVE LEVEL"));
	}

}

void ATheCubeCharacter::LoadCurrentLevel()
{
	if (!GetWorld())return;
	FName CurrentLevelName = *GetWorld()->GetName();
	if (CurrentLevelName == "ThirdPersonMap")return;

	if (MyGameInstance && MyGameInstance->GameData)
	{
		bMessageDone = MyGameInstance->GameData->bShowFirstMessage;
	}
	

	if (MyGameInstance && MyGameInstance->GameData)
	{
		ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
		if (ControllerCube) 
		{
			/*FString CurrentLevelName = MyGameInstance->GameData->LevelName;
			ControllerCube->ChangeLevel(CurrentLevelName);
			UE_LOG(LogTemp, Warning, TEXT("LOAD MAP"));*/
		}
		
	
	}
}

void ATheCubeCharacter::SaveFirstMessage()
{
	if (MyGameInstance) 
	{
		MyGameInstance->SaveFirstMessage(bMessageDone);
		UE_LOG(LogTemp, Warning, TEXT("SAVE MY FIRST MESSAGE"));
	}
	
}

void ATheCubeCharacter::AddControlWid()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (ControllerCube && GetWorld())
	{

		FName CurrentLevelName = *GetWorld()->GetName();
		if (MyGameInstance && MyGameInstance->GameData)
		{
			bMessageDone = MyGameInstance->GameData->bShowFirstMessage;
			UE_LOG(LogTemp, Warning, TEXT("bMessageDone"));
		}
		if (CurrentLevelName == "ThirdPersonMap" && !bMessageDone)
		{
			ControllerCube->AddControlWidget();
			bMessageDone = true;
			//Crear un timer para que se llame a SaveFirstMessage porque parece que cuando inicia hay que esperar porque la instancia no esta aun

			SaveFirstMessage();
			UE_LOG(LogTemp, Warning, TEXT("AddControlWid"));
		}

	}
}
void ATheCubeCharacter::PlayCamaraShake()
{
	ControllerCube = ControllerCube == nullptr ? Cast <ACubeController>(Controller) : ControllerCube;
	if (CameraShake && ControllerCube)
	{
		ControllerCube->ClientStartCameraShake(CameraShake);
		UE_LOG(LogTemp, Warning, TEXT("PlayCamaraShake"));
	}
}