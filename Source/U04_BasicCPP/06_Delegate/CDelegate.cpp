#include "CDelegate.h"
#include "Global.h"

void ACDelegate::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACDelegate::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACDelegate::ActorEndOverlap);
}

void ACDelegate::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnDelegateBegin.IsBound())
		OnDelegateBegin.Execute();

	if (OnRetValOneParam.IsBound())
	{
		FString str = OnRetValOneParam.Execute(FLinearColor::MakeRandomColor());
		str = "Random Color is " + str;
		CLog::Print(str);
	}
}

void ACDelegate::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnDelegateEnd.IsBound())
		OnDelegateEnd.Execute();
}
