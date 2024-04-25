// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/Public/Hud/ExLoginWidget.h"

#include "Center/ExLoginGameMode.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "KBEnginePlugins/Engine/KBEMain.h"

void UExLoginWidget::InitWidget() {
	this->TxtClientVersion->SetText(FText::FromString("ClientVersion: " + UKBEMain::getClientVersion()));
	this->TxtClientScriptVersion->SetText(FText::FromString("ClientScriptVersion: " + UKBEMain::getClientScriptVersion()));
	this->TxtServerVersion->SetText(FText::FromString("ServerVersion: " + UKBEMain::getServerVersion()));
	this->TxtServerScriptVersion->SetText(FText::FromString("ServerScriptVersion: " + UKBEMain::getServerScriptVersion()));
}

void UExLoginWidget::LoginEvent() {
	FString UserName = this->EditUserName->GetText().ToString();
	FString Password = this->EditPassword->GetText().ToString();
	if (UserName.IsEmpty() || Password.IsEmpty()) {
		UE_LOG(LogTemp, Error, TEXT("UserName or Password Can Not Be None"));
		return;
	}
	TArray<uint8> LoginData;
	FString ProjectName("Kbe");
	for (int i = 0; i < ProjectName.Len(); ++i) {
		LoginData.Add((uint8)ProjectName[i]);
	}
	this->LoginGameMode->KbeMain->login(UserName, Password, LoginData);
}
void UExLoginWidget::RegisterEvent() {
	FString UserName = this->EditUserName->GetText().ToString();
	FString Password = this->EditPassword->GetText().ToString();
	if (UserName.IsEmpty() || Password.IsEmpty()) {
		UE_LOG(LogTemp, Error, TEXT("UserName or Password Can Not Be None"));
		return;
	}
	TArray<uint8> LoginData;
	FString ProjectName("Kbe");
	for (int i = 0; i < ProjectName.Len(); ++i) {
		LoginData.Add((uint8)ProjectName[i]);
	}
	this->LoginGameMode->KbeMain->createAccount(UserName, Password, LoginData);
}
