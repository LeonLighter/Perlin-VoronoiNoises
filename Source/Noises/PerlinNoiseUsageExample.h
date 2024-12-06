// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinNoiseUsageExample.generated.h"

UCLASS()
class NOISES_API APerlinNoiseUsageExample : public AActor
{
	GENERATED_BODY()

public:
	APerlinNoiseUsageExample();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	int32 TextureWidth = 256;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	int32 TextureHeight = 256;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	float NoiseScale = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	int32 Octaves = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	float Persistence = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	float Frequencies = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise Generation")
	int32 Seed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noise Generation")
	class UTexture2D* GeneratedNoiseTexture;

	UFUNCTION(BlueprintCallable, Category = "Noise Generation")
	UTexture2D* GeneratePerlinNoiseTexture();
	
};
