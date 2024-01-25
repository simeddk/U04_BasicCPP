#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDropBox.generated.h"

UCLASS()
class U04_BASICCPP_API ACDropBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDropBox();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void RandomDrop(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Boxes[3];

private:
	class UMaterialInstanceDynamic* DynamicMaterials[3];
	FVector OriginLocation[3];

	int32 Index;
};
