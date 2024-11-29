// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TheCubeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UMaterialInterface;
struct FInputActionValue;
class UNiagaraSystem;
class USoundBase;
class UNiagaraComponent;
class UCubeGameInstance;
UENUM(BlueprintType)
enum class EColorState : uint8
{
	EWS_Idle UMETA(DisplayName = "Initial State"),
	EWS_FirstColor UMETA(DisplayName = "FirstColor"),
	EWS_SecondColor UMETA(DisplayName = "SecondColor"),
	EWS_ThirdColor UMETA(DisplayName = "ThirdColor"),
	EWS_ForthColor UMETA(DisplayName = "ForthColor"),
	EWS_MAXSTATE UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EPlayerState : uint8 
{
	EPS_Alive UMETA(DisplayName = "Alive State"),
	EPS_Dead UMETA(DisplayName = "Dead State"),
	EPS_LevelPassed UMETA(DisplayName = "LevelPassed"),
	EPS_MAXSTATE UMETA(DisplayName = "DefaultMAX")
};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATheCubeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ImpulseFrontAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateOpositeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ScrollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShowControlAction;

public:
	ATheCubeCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
		
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	void FellOutOfWorld(const UDamageType& dmgType)override;
	void ShowControlStarted();
	void ShowControlCompleted();
private:
	void PauseGame();
	//Zoom-----
	void ZoomCamera(const FInputActionValue& ValueZ);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float MinZoom = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	float MaxZoom = 1500.0f;
	//---Impulse-----
	void AddImpulse();
	bool bImpulsed = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpForward, meta = (AllowPrivateAccess = "true"))
	float SaltoAdelante = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpForward, meta = (AllowPrivateAccess = "true"))
	float DashSpeed = 650.f;
	void ResetbImpulse();
	FVector PlaneNormal = FVector(1.0f, 0.0f, 0.0f);
	FTimerHandle AddImpulseTimer;
	FTimerHandle SaveFirstMessageTimer;
	UPROPERTY(VisibleAnywhere, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	EColorState ColorState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpForward, meta = (AllowPrivateAccess = "true"))
	float SaltoDash = 50.f;

	//------DoubleJump-----

	void DoubleJump();
	void LaunchForward();
	virtual void Landed(const FHitResult& Hit) override;
	bool bWearejumping = false;
	int32 ConteoDelSalto = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JumpForward, meta = (AllowPrivateAccess = "true"))
	float SaltoVertical = 500.f;
	void RotateWorld(float RotationAmount);
	void RotateClockwise(const FInputActionValue& RoTa);
	void RotateCounterClockwise(const FInputActionValue& RoTe);
	void EffectOnDash();
	//---Materrial//--
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* FirstColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* SecondColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ThirdColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ForthColor;
	//----Rotation

	FRotator StartRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	FRotator TargetRotation;
	bool bIsRotating = false;
	float RotationSpeed = 90.0f; // Grados por segundo, ajusta según lo que necesites
	FTimerHandle RotationTimerHandle;
	void UpdateRotation();

	//----Salto sobre la pared
	void CheckWall();
	void GravityWall(bool IsThereAWall);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	float InterpSpeedWall = 1000.f; //La velocidad con la que bajamos al jugador cuando toca pared
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Colors, meta = (AllowPrivateAccess = "true"))
	float ForwardPush = -350.f;
	bool TheresAWall = false; //Esta la usamos para usar la funcion GravityWall
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* NiagaraEffectWall;
	UPROPERTY(EditAnywhere, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	float OffSetEffectWall = 35.f;
	UPROPERTY()
	class ACubeController* ControllerCube;
	void AddDeadWidget();
	void RemoveDeadWidget();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NiagaraDashEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	float OffsetDistance;
	bool bAlreadyDead = false;
	//-------------

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CapMesh;

	//-------- Sounds

	UFUNCTION()
	void PlaySound(USoundBase* Sound, FVector Location);

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* JUmpSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* JUmpDoubleSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DashSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DeadSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* LandedSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* MotorSound;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* AccelerateSound;

	//------AfterDie
	void AddAfterDieWid();
	void AddControlWid();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState", meta = (AllowPrivateAccess = "true"))
	EPlayerState StateOfThePlayer;
	FTimerHandle ShowWidDedHandle;
	//------GameInstance

	UPROPERTY()
	UCubeGameInstance* MyGameInstance; //Instancia del juego 
	void SaveCurrentLevel();
	void LoadCurrentLevel();
	void SaveFirstMessage();
	bool bMessageDone = false;

	//-----Camera Shake
	UPROPERTY(EditAnywhere, Category = "Shake")
	TSubclassOf <class UCameraShakeBase> CameraShake;
	void PlayCamaraShake();
public:
	void AddInfoWidget();
	void SetTextInfo(FString TextInfo);
	void SetPlayerState(EPlayerState StatePlayer);
	void SetColorState(EColorState State);
	bool GetbImpulsed() const { return bImpulsed; }
	bool bGoalReached = false; //Usemos este bool para todos los widgets
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE EColorState GetColorState() const { return ColorState; }
};

