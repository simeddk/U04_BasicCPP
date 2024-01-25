#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPrintLog.generated.h"

UCLASS()
class U04_BASICCPP_API ACPrintLog : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPrintLog();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	float RunningTime;
};
