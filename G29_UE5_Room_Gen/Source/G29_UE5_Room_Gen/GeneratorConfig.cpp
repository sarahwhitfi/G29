// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorConfig.h"
#include "../Source/Runtime/XmlParser/Public/XmlFile.h"

// Sets default values for this component's properties
UGeneratorConfig::UGeneratorConfig()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	numRooms = 0;
}


// Called when the game starts
void UGeneratorConfig::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UGeneratorConfig::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGeneratorConfig::ParseConfigFile(FString fPath, int& parsedNumRooms)
{
	FXmlFile* configFile = new FXmlFile(fPath);
	if (!configFile->IsValid()) {
		UE_LOG(LogClass, Error, TEXT("COULDNT LOAD CONFIG FILE! Provided path: %s"), *fPath);
		delete configFile; 
		return;
	}

	FXmlNode* rootNode = configFile->GetRootNode();
	TArray<FXmlNode*> childNodes = rootNode->GetChildrenNodes();

	// for now just look for NumRooms tag
	for (FXmlNode* child : childNodes) {
		FString currentTag = child->GetTag();
		FString nodeStr = child->GetContent();

		// get and convert value to int
		if (currentTag == "NumRooms") {
			int conversion = FCString::Atoi(*nodeStr);

			// if conversion fails, the value will be zero. numRooms should never be zero anyway
			if (conversion == 0) {
				UE_LOG(LogClass, Error, TEXT("Couldn't get a valid value for NumRooms"));
				continue;
			}

			parsedNumRooms = conversion;
		}
	}

}

