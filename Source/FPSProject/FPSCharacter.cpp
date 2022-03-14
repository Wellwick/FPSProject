// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create the first person camera component
    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    check(FPSCameraComponent != nullptr);

    // Attach camera to capsule component
    FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

    // Position camera slightly above eyes
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

    // Enable the pawn to control camera rotation
    FPSCameraComponent->bUsePawnControlRotation = true;

    // Create a first person mesh component for the owning player
    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    check(FPSMesh != nullptr);

    // Only the owning player can see the mesh
    FPSMesh->SetOnlyOwnerSee(true);

    // Attach the FPS mesh to the FPS camera
    FPSMesh->SetupAttachment(FPSCameraComponent);

    // Disable some environmental shadows to preserve the illusion of a single mesh
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    // Hide the base mesh
    check(GetMesh() != nullptr);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    check(GEngine != nullptr);

    // Display a six second debug message
    GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, TEXT("We are using FPSCharacter."));
    FString string = GetMesh()->GetFullName();
    GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, string);
    GetMesh()->GetFName().ToString(string);
    GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, string);

    GetMesh()->SetOwnerNoSee(true);
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind player movement to Project Input Axis (WASD)
    PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

    // Bind player look to mouse
    PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

    // Bind jump to spacebar
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}

void AFPSCharacter::MoveForward(float value) {
    // Find out which was is "forward" and record that the player wants to move
    // that way
    FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(direction, value);
}

void AFPSCharacter::MoveRight(float value) {
    // Find out which was is "right" and record that the player wants to move
    // that way
    FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(direction, value);
}

void AFPSCharacter::StartJump() {
    bPressedJump = true;
}

void AFPSCharacter::StopJump() {
    bPressedJump = false;
}
