// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginActor.h"
#include "Core/PlayFabClientAPI.h"
// Sets default values
ALoginActor::ALoginActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoginActor::BeginPlay()
{
	Super::BeginPlay();

	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	PlayFab::ClientModels::FLoginWithCustomIDRequest Request;

	Request.CustomId = TEXT("GettingPlayFabStartedGuide");

	Request.CreateAccount = true;

	UE_LOG(LogTemp, Log, TEXT("Login Actor has setup the login request."));

	ClientAPI->LoginWithCustomID(Request,
		PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &ALoginActor::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &ALoginActor::OnError));
	
}

void ALoginActor::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
	UE_LOG(LogTemp, Log, TEXT("This is my first successful PlayFab API call."));
}

void ALoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Unknown nightmare with the first PlayFab API call. Error:\n%s"),
		*ErrorResult.GenerateErrorReport());
}


// Called every frame
void ALoginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

