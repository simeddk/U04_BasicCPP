#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CAutoFireWidget.generated.h"

UCLASS()
class U04_BASICCPP_API UCAutoFireWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnAutoFire();

	UFUNCTION(BlueprintImplementableEvent)
		void OffAutoFire();
};
