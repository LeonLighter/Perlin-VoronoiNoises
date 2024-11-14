// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PerlinNoise.generated.h"


/**
 * create a perlin noise class with a static function to generate perlin noise using a octaves and a frequency on a
 * 2D grid of size width x height and return the result in a 2D texture
 */
UCLASS()
class NOISES_API UPerlinNoise : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	
	
};
