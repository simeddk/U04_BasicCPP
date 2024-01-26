#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UCLASS()
class U04_BASICCPP_API ACRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	static ACRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsAiming() { return bAiming; }

	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE void ToggleAutoFire() {  bAutoFire = !bAutoFire; }

public:
	void Equip();
	void Begin_Equip();
	void End_Equip();

	void Unequip();
	void Begin_Unequip();
	void End_Unequip();

	void Begin_Aim();
	void End_Aim();

	void Begin_Fire();
	void End_Fire();

	void Firing();


private:
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float PitchSpeed = 0.25f;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float LimitPitch = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		class UAnimMontage* GrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		class UAnimMontage* UngrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TSubclassOf<UCameraShake> ShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TSubclassOf<class ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class USoundCue* FireSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UMaterialInstanceConstant* DecalMaterial;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;

	bool bEquipping; //Is Playing Montages
	bool bEquipped;  //Used In AnimInstance
	bool bAiming;	 //Is R-Button Pressed
	bool bFiring;	 //Is L-Button Pressed
	bool bAutoFire;	 //Is 'B' Button Toggle

	FTimerHandle AutoFireTimer;

	float CurrentPitch;
};
