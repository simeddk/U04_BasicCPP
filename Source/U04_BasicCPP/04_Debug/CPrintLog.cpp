#include "CPrintLog.h"
#include "Global.h"

ACPrintLog::ACPrintLog()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACPrintLog::BeginPlay()
{
	Super::BeginPlay();
	
	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2, 20.f);
	CLog::Print(4, 2, 20.f, FColor::Emerald);
	CLog::Print("Test");
	CLog::Print(FVector(999, 999, 999));
	CLog::Print(GetActorRotation());

	CLog::Log(777);
	CLog::Log(PI);
	CLog::Log("Log Test");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__);
	CLog::Log(__FUNCTION__, __LINE__);
	PrintLine();
}

void ACPrintLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	CLog::Print(RunningTime, 100);
}

