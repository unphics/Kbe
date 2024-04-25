// Fill out your copyright notice in the Description page of Project Settings.


#include "Kbe/Public/Player/ExLoginController.h"

void AExLoginController::BeginPlay() {
	Super::BeginPlay();

	// 设置游戏窗口大小
	ConsoleCommand(FString::Printf(TEXT("r.setres %dx%dw"), static_cast<uint32_t>(this->ScreenSize.X), static_cast<uint32_t>(this->ScreenSize.Y)));

	this->bShowMouseCursor = true;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	this->SetInputMode(InputMode);
}
