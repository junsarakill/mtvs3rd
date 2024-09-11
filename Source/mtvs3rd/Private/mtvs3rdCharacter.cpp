// Copyright Epic Games, Inc. All Rights Reserved.

#include "mtvs3rdCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include "../../../../Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// Amtvs3rdCharacter

// 생성자에서 Delegate 초기화 시에 Callback 함수 등록
Amtvs3rdCharacter::Amtvs3rdCharacter() : CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
, FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionComplete)), 
JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplate))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void Amtvs3rdCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	GetOnlineSubsystem();
}

/*초기화 단계에서 OnlineSubsystem에 접근하여 OnlineSessionInterface을 받아온다.
OnlineSessionInterface는 매치 메이킹 수행은 물론 플레이어가 온라인 게임을 찾아 참가할 수 있도록 하기 위해 필요한 것들을 배후에 미리 구성하는 플랫폼 전용 함수성을 제공한다.
OnlineSubsystem을 사용하는데 필수적이다.*/
void Amtvs3rdCharacter::GetOnlineSubsystem()
{
	// IOnlineSubsystem 받아오기
	IOnlineSubsystem * OnlineSubSystem = IOnlineSubsystem::Get();
	if (OnlineSubSystem)
	{
		// IOnlineSessionPtr 받아오기
		OnlineSessionInterface = OnlineSubSystem->GetSessionInterface();

		//IOnlineSessionPtr 이름 출력
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Orange,
			FString::Printf(TEXT("Subsystem 이름 : %s"),*OnlineSubSystem->GetSubsystemName().ToString()
			)
			);
		}
	}

}


void Amtvs3rdCharacter::CreateGameSession()  // 섹션 생성
{
	if (!OnlineSessionInterface.IsValid())  //OnlineSessionInterface가 유효한지 체크한다.
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));

		return;
	}

	auto ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr) // 이미 세션이 존재한다면 기존 세션을 삭제한다.
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("Destroy session : %s"), NAME_GameSession));
	}

	//세션 생성 완료 후 호출될 delegate 리스트에 CreateSessionCompleteDelegate 추가
	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());

	SessionSettings->bIsLANMatch = false;       // Lan 연결이 가능여부
	SessionSettings->NumPublicConnections = 4;  // 최대 접속 가능 수
	SessionSettings->bAllowJoinInProgress = true; // Session 진행중에 접속 허용
	SessionSettings->bAllowJoinViaPresence = true; // 세션 참가 지역을 현재 지역으로 제한  (스팀의 presence 사용)
	SessionSettings->bShouldAdvertise = true;   // 현재 세션을 광고할지 (스팀의 다른 플레이어에게 세션 홍보 여부)
	SessionSettings->bUsesPresence = true;		// 현재 지역에 세션 표시
	SessionSettings->bUseLobbiesIfAvailable = true;	// 플랫폼이 지원하는 경우 로비 API 사용
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing); 
	/*FOnlineSessionSettings의 Set함수는 SessionSetting할 때 Key와 Value 짝으로 옵션을 세팅해주는 함수다.
위 코드는 세션의 MatchType을 '모두에게 열림(FreeForAll)'으로 설정하고, 온라인 서비스와 핑을 통해 세션을 홍보할 수 있게 설정하는 코드이다.*/

	// Local Player를 호스트로 설정하여 하여 세션 생성하기
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void Amtvs3rdCharacter::JoinGameSession()
{
	if (!OnlineSessionInterface.IsValid()) // 세션 인터페이스 유효성 검사
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Game Session Interface is invailed")));

		return;
	}

	// Find Session Complete Delegate 등록
	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);

	// Find Game Session
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 10000; // 검색 결과로 나오는 세션 수 최대값
	SessionSearch->bIsLanQuery = false; // LAN 사용 여부
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);  
	// 찾을 세션 쿼리를 현재로 설정한다

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());

}

//이 함수에서는 세션에 참여했다면 참여한 세션의 IP 주소로 접속한다.
void Amtvs3rdCharacter::OnJoinSessionComplate(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!OnlineSessionInterface.IsValid())
		return;

	// 세션에 조인했다면 IP Address얻어와서 해당 서버에 접속
	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Connect String : %s"), *Address));

		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

//이 함수에서는 세션들을 찾고 세션의 매치 타입이 'FreeForAll'일 경우, 세션에 참가한다.
void Amtvs3rdCharacter::OnFindSessionComplete(bool bWasSuccessful)
{
	if (!OnlineSessionInterface.IsValid() || !bWasSuccessful)
		return;

	for (auto Result : SessionSearch->SearchResults)
	{
		FString Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;

		// 매치 타입 확인하기
		FString MatchType;
		Result.Session.SessionSettings.Get(FName("MatchType"), MatchType);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Session ID : %s / Owner : %s"), *Id, *User));

		// 세션의 매치 타입이 "FreeForAll"일 경우 세션 참가
		if (MatchType == FString("FreeForAll"))
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("Joining Match Type : %s"), *MatchType));

			// Join Session Complete Delegate 등록 
			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, Result);
		}
	}
}

void Amtvs3rdCharacter::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString::Printf(TEXT("Created session : %s"), *SessionName.ToString()));

// 		UWorld* World = GetWorld();
// 		if (World)
// 			World->ServerTravel(FString("/Game/ThirdPerson/Maps/ThirdPersonMap?listen"));
	}

	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void Amtvs3rdCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Amtvs3rdCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Amtvs3rdCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void Amtvs3rdCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void Amtvs3rdCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}