#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CAnimInstance.h"
#include "CRifle.h"
#include "Widgets/CAimWidget.h"
#include "Widgets/CAutoFireWidget.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//MeshComp
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UCAnimInstance> animClass;
	CHelpers::GetClass<UCAnimInstance>(&animClass, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animClass);

	//SpringArmComp
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	//CameraComp
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	//Movement
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	//Get Widget ClassRef
	CHelpers::GetClass<UCAimWidget>(&AimWidgetClass, "WidgetBlueprint'/Game/Widgets/WB_Aim.WB_Aim_C'");
	CHelpers::GetClass<UCAutoFireWidget>(&AutoFireWidgetClass, "WidgetBlueprint'/Game/Widgets/WB_AutoFire.WB_AutoFire_C'");

}

void ACPlayer::BeginPlay()
{
	//Set Dynamic Material
	UMaterial* bodyMaterialAsset;
	CHelpers::GetAssetDynamic<UMaterial>(&bodyMaterialAsset, "Material'/Game/Character/Materials/M_UE4Man_Body.M_UE4Man_Body'");
	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterialAsset, this);
	GetMesh()->SetMaterial(0, BodyMaterial);

	UMaterialInstanceConstant* logoMaterialAsset;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logoMaterialAsset, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_ChestLogo.M_UE4Man_ChestLogo'");
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterialAsset, this);
	GetMesh()->SetMaterial(1, LogoMaterial);

	//Spawn & Equip Rifle
	Rifle = ACRifle::Spawn(GetWorld(), this);
	OnRifle();

	//Create Widgets
	if (!!AimWidgetClass)
	{
		AimWidget = CreateWidget<UCAimWidget, APlayerController>(GetController<APlayerController>(), AimWidgetClass);
		AimWidget->AddToViewport();
		AimWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (!!AutoFireWidgetClass)
	{
		AutoFireWidget = CreateWidget<UCAutoFireWidget, APlayerController>(GetController<APlayerController>(), AutoFireWidgetClass);
		AutoFireWidget->AddToViewport();
	}

	Super::BeginPlay();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACPlayer::OnRun);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACPlayer::OffRun);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPlayer::OnAutoFire);
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = Camera->GetForwardVector();

	FVector cameraLocation = Camera->GetComponentToWorld().GetLocation();
	OutAimStart = cameraLocation + OutAimDirection  * 100.f;
	
	FVector randomDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDirection, 0.2f);
	OutAimEnd = cameraLocation + randomDirection * 3000.f;
}

void ACPlayer::OnTarget()
{
	AimWidget->OnTarget();
}

void ACPlayer::OffTarget()
{
	AimWidget->OffTarget();
}

void ACPlayer::OnMoveForward(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(InAxis);
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	AddControllerPitchInput(InAxis);
}

void ACPlayer::OnRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::OnRifle()
{
	if (Rifle->IsEquipped())
	{
		Rifle->Unequip();
		return;
	}

	Rifle->Equip();
}

void ACPlayer::OnAim()
{
	CheckFalse(Rifle->IsEquipped());
	CheckTrue(Rifle->IsEquipping());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->TargetArmLength = 100.f;
	SpringArm->SocketOffset = FVector(0, 30, 10);

	ZoomIn();

	Rifle->Begin_Aim();

	AimWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	CheckFalse(Rifle->IsEquipped());
	CheckTrue(Rifle->IsEquipping());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	ZoomOut();

	Rifle->End_Aim();

	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::OnFire()
{
	Rifle->Begin_Fire();
}

void ACPlayer::OffFire()
{
	Rifle->End_Fire();
}

void ACPlayer::OnAutoFire()
{
	CheckTrue(Rifle->IsFiring());

	Rifle->ToggleAutoFire();

	Rifle->IsAutoFire() ? AutoFireWidget->OnAutoFire() : AutoFireWidget->OffAutoFire();
}

void ACPlayer::SetBodyColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

