#include "CSphereTrace.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"

ACSphereTrace::ACSphereTrace()
{
	CHelpers::CreateSceneComponent(this, &Particle, "Particle");

	UParticleSystem* particleAssset;
	CHelpers::GetAsset<UParticleSystem>(&particleAssset, "ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_waterBallHit.P_ky_waterBallHit'");
	Particle->SetTemplate(particleAssset);
	Particle->SetRelativeScale3D(FVector(2.f));
	Particle->bAutoActivate = false;
}

void ACSphereTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSphereTrace::DoSphereTrace(AActor* OverlappedActor, AActor* OtherActor)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	CheckNull(character);

	FVector start = GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignores;
	TArray<FHitResult> hitResults;

	if (UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		start,
		end,
		1000,
		objectTypes,
		false,
		ignores,
		EDrawDebugTrace::ForDuration,
		hitResults,
		true
	))
	{
		Particle->ResetParticles();
		Particle->SetActive(true);

		for (FHitResult hitResult : hitResults)
		{
			UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (!!meshComp && meshComp->IsSimulatingPhysics())
			{
				meshComp->AddRadialImpulse(start, 1000, 15e+6f / meshComp->GetMass(), ERadialImpulseFalloff::RIF_Linear);
			}
		}
	}

		
}

