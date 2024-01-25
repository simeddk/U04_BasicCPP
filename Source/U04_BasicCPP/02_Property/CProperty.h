#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class U04_BASICCPP_API ACProperty : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		int NumA = 10;

	UPROPERTY(EditInstanceOnly)
		int NumB = 20;

	UPROPERTY(EditDefaultsOnly)
		int NumC = 20;

	UPROPERTY(VisibleAnywhere)
		float RealA = 77.7f;

	UPROPERTY(VisibleInstanceOnly)
		float RealB = 3.14f;

	UPROPERTY(VisibleDefaultsOnly)
		float RealC = 9.99f;

	int Number99 = 100;

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FString message = "HAHA";

private:
	UPROPERTY(EditInstanceOnly)
		class ACHelloWorld* Object;

};
