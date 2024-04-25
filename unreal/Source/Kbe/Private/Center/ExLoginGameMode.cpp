// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/ExLoginGameMode.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Center/ExKbeClient.h"
#include "Hud/ExLoginWidget.h"
#include "KBEnginePlugins/Engine/KBEngine.h"
#include "Kismet/GameplayStatics.h"

void AExLoginGameMode::BeginPlay() {
	// 每次进入到登录界面时先清理一遍KBE, 否则KBE插件缓存内容会一直存在
	KBEngine::KBEngineApp::getSingleton().reset();
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Begin Create Login Widget"));
	this->LoginWidget = CreateWidget<UExLoginWidget>(this->GetWorld(), this->LoginWidgetClass);
	UE_LOG(LogTemp, Log, TEXT("Finish Create Login Widget"));
	
	this->LoginWidget->AddToViewport();
	this->LoginWidget->LoginGameMode = this;
	this->LoginWidget->InitWidget();

	for (TActorIterator<AExKbeClient> ActorIt(this->GetWorld()); ActorIt; ++ActorIt) {
		this->KbeMain = (*ActorIt)->KbeMain;
	}
}

void AExLoginGameMode::InstallEvent() {
	Super::InstallEvent();
	
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	KBENGINE_REGISTER_EVENT("OnLoginSuccessfully", OnLoginSuccessfully);
}

void AExLoginGameMode::OnCreateAccountResult(const UKBEventData* EventData) {
	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("ErrorCode: ")) +
		FString::FromInt(ServerData->errorCode) + FString(TEXT("; ErrorStr :")) + ServerData->errorStr);
}

void AExLoginGameMode::OnLoginFailed(const UKBEventData* EventData) {
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("FailedCode: ")) +
		FString::FromInt(ServerData->failedcode) + FString(TEXT("; ErrorStr :")) + ServerData->errorStr);
}

void AExLoginGameMode::OnVersionNotMatch(const UKBEventData* EventData) {
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("ClientVersion: ")) +
		ServerData->clientVersion + FString(TEXT("; ServerVersion :")) + ServerData->serverVersion);
}

void AExLoginGameMode::OnScriptVersionNotMatch(const UKBEventData* EventData) {
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("ClientScriptVersion: ")) +
		ServerData->clientScriptVersion + FString(TEXT("; ServerScriptVersion :")) + ServerData->serverScriptVersion);
}

void AExLoginGameMode::OnLoginBaseappFailed(const UKBEventData* EventData) {
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("FailedCode: ")) +
		FString::FromInt(ServerData->failedcode) + FString(TEXT("; ErrorStr :")) + ServerData->errorStr);
}

void AExLoginGameMode::OnLoginBaseapp(const UKBEventData* EventData) {
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("EventName: ")) +
		ServerData->eventName);
}

void AExLoginGameMode::OnLoginSuccessfully(const UKBEventData* EventData) {
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("Entity_uuid: ")) +
		FString::FromInt(ServerData->entity_uuid) + FString(TEXT("; Entity_id :")) + FString::FromInt(ServerData->entity_id));
	// 登录成功后跳转到选择角色界面
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoleMap"));
}
