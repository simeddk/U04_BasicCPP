#include "CBlueprintOverride.h"
#include "Global.h"
#include "Characters/CPlayer.h"

void ACBlueprintOverride::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ACBlueprintOverride::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBlueprintOverride::ActorEndOverlap);
}

void ACBlueprintOverride::ResetPlayerColor_Implementation()
{
	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACPlayer* player = Cast<ACPlayer>(character);
	CheckNull(player);

	player->SetBodyColor(FLinearColor(0.450980, 0.403922, 0.360784, 0.000000));
}

void ACBlueprintOverride::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ChangePlayerColor();
}

void ACBlueprintOverride::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ResetPlayerColor();
}
