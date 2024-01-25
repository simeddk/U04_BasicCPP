#include "CLineTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Characters/CPlayer.h"
#include "CVertex.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Text, "Text", Root);

	Text->SetTextRenderColor(FColor::Black);
	Text->SetText(GetName());
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACVertex::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	Vertices[0] = Cast<ACVertex>(actors[0]);
	Vertices[1] = Cast<ACVertex>(actors[1]);

	OnLineTrace.AddDynamic(this, &ACLineTrace::Ragdoll);
}

void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = Vertices[0]->GetActorLocation();
	FVector end = Vertices[1]->GetActorLocation();

	//DrawDebugLine(GetWorld(), start, end, FColor::Red);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(Vertices[0]);
	ignoreActors.Add(Vertices[1]);

	FHitResult hitResult;

	if (UKismetSystemLibrary::LineTraceSingleByProfile
	(
		GetWorld(),
		start,
		end,
		"Pawn",
		false,
		ignoreActors,
		EDrawDebugTrace::ForOneFrame,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red
	))
	{
		if (OnLineTrace.IsBound())
			OnLineTrace.Broadcast(hitResult.GetActor(), FLinearColor::Yellow);
	}

}

void ACLineTrace::Ragdoll(AActor* InActor, FLinearColor InColor)
{
	ACPlayer* player = Cast<ACPlayer>(InActor);
	CheckNull(player);

	player->GetMesh()->GlobalAnimRateScale = 0.f;
	player->GetMesh()->SetSimulatePhysics(true);
	player->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	player->GetMesh()->AddImpulse(FVector(-1e+5f, 0, 0));
}

