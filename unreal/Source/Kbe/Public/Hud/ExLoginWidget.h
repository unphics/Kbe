// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExLoginWidget.generated.h"

class UEditableTextBox;
class UTextBlock;
class AExLoginGameMode;

/**
 * 
 */
UCLASS()
class KBE_API UExLoginWidget : public UUserWidget {
	GENERATED_BODY()
public:
	void InitWidget();
	UFUNCTION(BlueprintCallable)
	void LoginEvent();
	UFUNCTION(BlueprintCallable)
	void RegisterEvent();
public:
	AExLoginGameMode* LoginGameMode;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditUserName;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EditPassword;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtClientVersion;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtClientScriptVersion;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtServerVersion;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TxtServerScriptVersion;
	
};
