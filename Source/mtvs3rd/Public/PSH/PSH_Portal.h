// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSH_HttpDataTable.h"
#include "PSH_Portal.generated.h"

UCLASS()
class MTVS3RD_API APSH_Portal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSH_Portal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly,Category = Mesh)
	class USceneComponent * Root;

	UPROPERTY(EditDefaultsOnly,Category = Mesh)
	class UStaticMeshComponent * mesh;

	UPROPERTY(EditDefaultsOnly,Category = widget)
	class UWidgetComponent * widget;

	UPROPERTY()
	class UPSH_PotalWidget * PotalWidget;

	UPROPERTY(EditAnywhere , Category = Tags)
	bool bisEndPotal;

	UPROPERTY(EditAnywhere , Category = Tags)
	FName TagetName;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerPotal)
	int32 PlayerCount;

	UPROPERTY()
	TArray<class ABS_VRPlayer*> PlayerArray; // 플레이어

	TArray<FPSH_HttpDataTable> PlayerDataArray;

	TArray<int> PlayerIdArray;

	int32 TestScroe = 50;

	int SetMeshPlayerID;

	UFUNCTION()
    void OnRep_PlayerPotal();

	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Setvisilbe(bool chek);


	void SetPortal();
	
	void GoPotal();
	UFUNCTION(Server,Reliable)
	void SRPC_GoPotal();
	UFUNCTION(NetMulticast,Reliable)
	void MRPC_GoPotal();

	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const;

private:

	UPROPERTY()
	//class Amtvs3rdCharacter* player;
	class ABS_VRPlayer* player;
	UPROPERTY()
	TArray<class AActor*> EndPotal;
};
