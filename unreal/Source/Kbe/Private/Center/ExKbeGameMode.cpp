
#include "Kbe/Public/Center/ExKbeGameMode.h"

#include "KBEnginePlugins/Engine/KBEngine.h"

AExKbeGameMode::AExKbeGameMode() {
	this->PrimaryActorTick.bCanEverTick = false;
}

void AExKbeGameMode::BeginPlay() {
	Super::BeginPlay();

	this->InstallEvent();
}

void AExKbeGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	this->UninstallEvent();
}

void AExKbeGameMode::InstallEvent() {
	// 注册最基本的回调事件(每个关卡都需要的)
	// 每个关卡都要的五个基本回调事件，三个连接相关的两个login
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectionState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);
}
void AExKbeGameMode::UninstallEvent() {
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void AExKbeGameMode::OnKicked(const UKBEventData* EventData) {
	const UKBEventData_onKicked* ServerData = Cast<UKBEventData_onKicked>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("OnKicked: FailedCode: ")) + 
		FString::FromInt(ServerData->failedcode) + FString(TEXT("; ErrorStr: ")) + ServerData->errorStr);
}

void AExKbeGameMode::OnDisconnected(const UKBEventData* EventData) {
	const UKBEventData_onDisconnected* ServerData = Cast<UKBEventData_onDisconnected>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("OnDisconnected: EventName: ")) + ServerData->eventName);	
}

void AExKbeGameMode::OnConnectionState(const UKBEventData* EventData) {
	const UKBEventData_onConnectionState* ServerData = Cast<UKBEventData_onConnectionState>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("OnConnectionState: Success: ")) +
		FString(ServerData->success?TEXT("true"):TEXT("false")) + FString(TEXT("; Address: ")) + ServerData->address);
}

void AExKbeGameMode::OnReloginBaseappSuccessfully(const UKBEventData* EventData) {
	const UKBEventData_onReloginBaseappSuccessfully* ServerData = Cast<UKBEventData_onReloginBaseappSuccessfully>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("OnReloginBaseappSuccessfully: EventName: ")) + ServerData->eventName);
	// 断线重连成功，停止重连操作
	this->StopReloginBaseapp();
}

void AExKbeGameMode::OnReloginBaseappFailed(const UKBEventData* EventData) {
	const UKBEventData_onReloginBaseappFailed* ServerData = Cast<UKBEventData_onReloginBaseappFailed>(EventData);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString(TEXT("OnReloginBaseappFailed: FailedCode: ")) +
		FString::FromInt(ServerData->failedcode) + FString(TEXT("; ErrorStr: ")) + ServerData->errorStr);
}

void AExKbeGameMode::StartReloginBaseapp() {
	if (!this->ReloginHandle.IsValid()) {
		this->GetWorld()->GetTimerManager().SetTimer(this->ReloginHandle, this, &AExKbeGameMode::OnReloginBaseappTimer, 1.f, true, 1.f);
	}
}
void AExKbeGameMode::StopReloginBaseapp() {
	if (this->ReloginHandle.IsValid()) this->GetWorld()->GetTimerManager().ClearTimer(this->ReloginHandle);
}
void AExKbeGameMode::OnReloginBaseappTimer() {
	// 断线重连事件
	KBEngine::KBEngineApp::getSingleton().reloginBaseapp();
}
