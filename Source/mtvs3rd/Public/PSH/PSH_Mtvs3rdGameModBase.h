// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "PSH_HttpDataTable.h"
#include "PSH_Mtvs3rdGameModBase.generated.h"


UCLASS()
class MTVS3RD_API APSH_Mtvs3rdGameModBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	APSH_Mtvs3rdGameModBase();



	// �÷��̾� �α��� �õ� �Ҷ�
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// �÷��̾� �α��� ����
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:

	UPROPERTY()
	class UPSH_GameInstance * Gi;

	// �÷��̾� ����ü
	FPSH_HttpDataTable PlayerData;

	UPROPERTY()
	class ABS_PlayerState * playerState; // �÷��̾� ���� ���� ���
	
	TMap<int,int> ChoiceNum;

	UPROPERTY(EditDefaultsOnly)
	int LastChoiceNum = 0;    // �Լ� ���� üũ ���� �ִ� �÷��̾� ������ ������ üũ�ϴ� �뵵.

	UPROPERTY(EditDefaultsOnly)
	int playerCount = 0;   // �ִ� �÷��̾� �� 

	UPROPERTY()
	class APSH_LastChoiceActor * ChoiceActor;

public:
	void SetData(FPSH_HttpDataTable Data);

	void LastChoice(int FromId, int ToId);

	FPSH_HttpDataTable GetData(int num);

	void ChekChoice();

	void SetActor(class APSH_LastChoiceActor * Actor);





	
private:
};
