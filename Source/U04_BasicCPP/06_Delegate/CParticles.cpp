#include "CParticles.h"
#include "Global.h"
#include "Particles/ParticleSystem.h"
#include "CEvent.h"

ACParticles::ACParticles()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");

	CHelpers::GetAsset(&Particles[0], "ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_laser01.P_ky_laser01'");
	CHelpers::GetAsset(&Particles[1], "ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_lightning1.P_ky_lightning1'");
	CHelpers::GetAsset(&Particles[2], "ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_waterBallHit.P_ky_waterBallHit'");
}

void ACParticles::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACEvent::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	ACEvent* eventTrigger = Cast<ACEvent>(actors[0]);
	CheckNull(eventTrigger);

	eventTrigger->OnEventOverlap.AddUFunction(this, "PlayParticle");
}

void ACParticles::PlayParticle(int32 InValue)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InValue], transform);
}

