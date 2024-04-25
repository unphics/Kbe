// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExKbeGameMode.generated.h"

class UKBEventData;

/**
 * 绑定一些每个场景都会用到的回调事件
 */
UCLASS()
class KBE_API AExKbeGameMode : public AGameModeBase {
	GENERATED_BODY()
public:
	AExKbeGameMode();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// 注册Kbe事件
	virtual void InstallEvent();
	// 注销Kbe事件
	virtual void UninstallEvent();

	virtual void OnKicked(const UKBEventData* EventData); // 被踢出服务器
	virtual void OnDisconnected(const UKBEventData* EventData); // 
	virtual void OnConnectionState(const UKBEventData* EventData);
	virtual void OnReloginBaseappSuccessfully(const UKBEventData* EventData); // 重连成功
	virtual void OnReloginBaseappFailed(const UKBEventData* EventData); // 重连失败
protected:
	// 为什么是baseapp而不是loginapp: 登录后loginapp会把数据转移到baseapp
	void StartReloginBaseapp();
	void StopReloginBaseapp();
	void OnReloginBaseappTimer(); // 绑定给定时器的事件
protected:
	FTimerHandle ReloginHandle;
};
