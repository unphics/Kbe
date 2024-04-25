
#include "Center/ExKbeClient.h"

#include "KBEnginePlugins/Engine/KBEMain.h"

AExKbeClient::AExKbeClient() {
	PrimaryActorTick.bCanEverTick = false;

	this->RootComponent = this->CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	this->KbeMain = this->CreateDefaultSubobject<UKBEMain>(TEXT("KbeMain"));
}

void AExKbeClient::BeginPlay() {
	Super::BeginPlay();
	
}

void AExKbeClient::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

