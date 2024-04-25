// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/ExKbeGameMode.h"
#include "ExLoginGameMode.generated.h"

class UKBEMain;
class UExLoginWidget;
class UKBEventData;
/**
 * 
 */
UCLASS()
class KBE_API AExLoginGameMode : public AExKbeGameMode {
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void InstallEvent() override;

	void OnCreateAccountResult(const UKBEventData* EventData); // 创建用户入口实体回调
	void OnLoginFailed(const UKBEventData* EventData); // 登录失败回调
	void OnVersionNotMatch(const UKBEventData* EventData); // 版本匹配回调
	void OnScriptVersionNotMatch(const UKBEventData* EventData); // 版本不匹配回调
	void OnLoginBaseappFailed(const UKBEventData* EventData); // 登录Baseapp失败回调
	void OnLoginBaseapp(const UKBEventData* EventData); //登录baseapp回调
	void OnLoginSuccessfully(const UKBEventData* EventData); // 登录成功回调，生成account后在__init__()时调用，在这里跳转到选择角色场景
public:
	UKBEMain* KbeMain;
protected:
	UExLoginWidget* LoginWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoginWidgetClass;
	
};
