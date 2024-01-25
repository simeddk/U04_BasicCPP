#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHelloWorld.generated.h"

UCLASS()
class U04_BASICCPP_API ACHelloWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	ACHelloWorld();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Print();

};
