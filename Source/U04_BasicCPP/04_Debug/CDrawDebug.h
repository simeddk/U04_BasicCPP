#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawDebug.generated.h"

UCLASS()
class U04_BASICCPP_API ACDrawDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDrawDebug();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "DrawDebug")
		FBox Box;

	UPROPERTY(EditAnywhere, Category = "DrawDebug")
		FVector RelativeLocation[4];

private:
	FVector GlobalLocation[4];

};
