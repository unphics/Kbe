// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExKbeClient.generated.h"

class UKBEMain;

UCLASS()
class KBE_API AExKbeClient : public AActor
{
	GENERATED_BODY()
public:	
	AExKbeClient();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere)
	UKBEMain* KbeMain;
};
