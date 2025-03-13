// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorConfig.h"
#include "../Source/Runtime/XmlParser/Public/XmlFile.h"
#include "Misc/Paths.h"

// Sets default values for this component's properties
UGeneratorConfig::UGeneratorConfig()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	numRooms = 0;
	minScale = 0.f;
	maxScale = 0.f;
	
	// get path to config file and call parser
	// XML File should have name "GeneratorConfig.xml" and be located in games source directory (same folder as cpp classes)
	FString gameSourcePath = FPaths::GameSourceDir();
	FString configPath = FPaths::Combine(gameSourcePath, TEXT("GeneratorConfig.xml"));
	
	ParseConfigFile(configPath, numRooms, minScale, maxScale);

	if (numRooms == 0) { UE_LOG(LogClass, Error, TEXT("numRooms value is still zero after parsing config file")) }
	if (minScale == 0.f) { UE_LOG(LogClass, Error, TEXT("minScale value is still zero after parsing config file")) }
	if (maxScale == 0.f) { UE_LOG(LogClass, Error, TEXT("maxScale value is still zero after parsing config file")) }
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

// parses through config file and gets number of rooms to be generated, minimum and maximum scale for room sizes (X and Y axis)
void UGeneratorConfig::ParseConfigFile(FString fPath, int &parsedNumRooms, float &parsedMinScale, float &parsedMaxScale)
{
	FXmlFile* configFile = new FXmlFile(fPath);
	if (!configFile->IsValid()) {
		UE_LOG(LogClass, Error, TEXT("COULDNT LOAD CONFIG FILE! Provided path: %s"), *fPath);
		delete configFile; 
		return;
	}

	FXmlNode* rootNode = configFile->GetRootNode();
	TArray<FXmlNode*> childNodes = rootNode->GetChildrenNodes();

	// iterate through all nodes 
	for (FXmlNode* child : childNodes) {
		FString currentTag = child->GetTag();
		FString nodeStr = child->GetContent();

		// get and convert NumRooms to int
		if (currentTag == "NumRooms") {
			int conversion = FCString::Atoi(*nodeStr);

			// if conversion fails, the value will be zero. numRooms should never be zero anyway
			if (conversion == 0) {
				UE_LOG(LogClass, Error, TEXT("Couldn't get a valid value for NumRooms"));
				continue;
			}

			parsedNumRooms = conversion;
		}

		// get and convert MinScale to float
		else if (currentTag == "MinScale") {
			float conversion = FCString::Atof(*nodeStr);

			// if conversion fails, the value will be zero. minScale should never be zero anyway
			if (conversion == 0.f) {
				UE_LOG(LogClass, Error, TEXT("Couldn't get a valid value for MinScale"));
				continue;
			}

			parsedMinScale = conversion;
		}

		// get and convert MaxScale to float
		else if (currentTag == "MaxScale") {
			float conversion = FCString::Atof(*nodeStr);

			// if conversion fails, the value will be zero. minScale should never be zero anyway
			if (conversion == 0.f) {
				UE_LOG(LogClass, Error, TEXT("Couldn't get a valid value for MaxScale"));
				continue;
			}

			parsedMaxScale = conversion;
		}
	}

	delete configFile;
}

