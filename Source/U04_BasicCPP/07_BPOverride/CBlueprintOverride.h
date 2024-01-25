#pragma once

#include "CoreMinimal.h"
#include "05_Collision/CBoxBase.h"
#include "CBlueprintOverride.generated.h"

UCLASS()
class U04_BASICCPP_API ACBlueprintOverride : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ChangePlayerColor();

	UFUNCTION(BlueprintNativeEvent)
		void ResetPlayerColor();
	
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
