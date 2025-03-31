// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneratorConfig.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class G29_UE5_ROOM_GEN_API UGeneratorConfig : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeneratorConfig();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int numRooms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float minScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float maxScale;

	void ParseConfigFile(FString fPath, int &parsedNumRooms, float &parsedMinScale, float &parsedMaxScale);
		
};
