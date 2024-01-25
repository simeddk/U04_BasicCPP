#include "CRifle.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Characters/IRifle.h"

ACRifle::ACRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(meshAsset);

	CHelpers::GetAsset(&GrabMontage, "/Game/Character/Animations/Rifle/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UngrabMontage, "/Game/Character/Animations/Rifle/Rifle_Ungrab_Montage");

	CHelpers::GetClass<UCameraShake>(&ShakeClass, "Blueprint'/Game/Player/BP_Shake.BP_Shake_C'");
}

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = InOwner;

	return InWorld->SpawnActor<ACRifle>(spawnParam);
}


void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	if (!!OwnerCharacter)
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bAiming);

	//LineTrace for Aim(HitScan)
	IIRifle* rifleCharacter = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifleCharacter);

	FVector start, end, direction;
	rifleCharacter->GetAimInfo(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Red);

	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(this);
	queryParam.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_PhysicsBody, queryParam))
	{
		AStaticMeshActor* otherActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!otherActor)
		{
			UStaticMeshComponent* otherComp = Cast<UStaticMeshComponent>(otherActor->GetRootComponent());
			if (!!otherComp)
			{
				if (otherComp->BodyInstance.bSimulatePhysics == true)
				{
					rifleCharacter->OnTarget();

					return;
				}
			}
		}
	}

	rifleCharacter->OffTarget();
}


void ACRifle::Equip()
{
	CheckTrue(bEquipping);
	CheckTrue(bEquipped);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ACRifle::End_Equip()
{
	bEquipping = false;
}

void ACRifle::Unequip()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UngrabMontage);
}

void ACRifle::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACRifle::End_Unequip()
{
	bEquipping = false;
}

void ACRifle::Begin_Aim()
{
	bAiming = true;
}

void ACRifle::End_Aim()
{
	bAiming = false;
}

void ACRifle::Begin_Fire()
{
	CheckFalse(bEquipped);
	CheckTrue(bEquipping);
	CheckFalse(bAiming);
	CheckTrue(bFiring);

	bFiring = true;

	Firing();
}

void ACRifle::End_Fire()
{
	bFiring = false;
}

void ACRifle::Firing()
{
	//Play Camera Shake
	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
	if (!!controller)
		controller->PlayerCameraManager->PlayCameraShake(ShakeClass);

	//LineTrace for AddImpulse
	IIRifle* rifleCharacter = Cast<IIRifle>(OwnerCharacter);
	CheckNull(rifleCharacter);

	FVector start, end, direction;
	rifleCharacter->GetAimInfo(start, end, direction);

	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(this);
	queryParam.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, queryParam))
	{
		AStaticMeshActor* otherActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!otherActor)
		{
			UStaticMeshComponent* otherComp = Cast<UStaticMeshComponent>(otherActor->GetRootComponent());
			if (!!otherComp)
			{
				if (otherComp->BodyInstance.bSimulatePhysics == true)
				{
					direction = otherActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					direction.Normalize();

					otherComp->AddImpulseAtLocation(direction * 3000.f, OwnerCharacter->GetActorLocation());

					return;
				} //if (bSimulatePhysics)
			} //if ( Cast<UStaticMeshComponent>)
		} // if (Cast<AStaticMeshActor>)
	} //if (LineTrace)

}


