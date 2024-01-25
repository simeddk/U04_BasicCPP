#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceSignatrue, class AActor*, InActor, FLinearColor, InColor);

UCLASS()
class U04_BASICCPP_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	UFUNCTION()
		void Ragdoll(class AActor* InActor, FLinearColor InColor);

public:
	UPROPERTY(BlueprintAssignable)
		FLineTraceSignatrue OnLineTrace;

private:
	class ACVertex* Vertices[2];
};
