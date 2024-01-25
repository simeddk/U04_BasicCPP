#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CDelegate.generated.h"

DECLARE_DELEGATE(FDelegateBeginSignature); //void Func()
DECLARE_DELEGATE(FDelegateEndSignature); //void Func()
DECLARE_DELEGATE_RetVal_OneParam(FString, FRetValOneParamSignature, FLinearColor); //FString Func(FLinearColor)

UCLASS()
class U04_BASICCPP_API ACDelegate : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	FDelegateBeginSignature OnDelegateBegin;
	FDelegateEndSignature OnDelegateEnd;
	FRetValOneParamSignature OnRetValOneParam;
};
