// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinNoise.h"
#include "Engine/Texture2D.h"


void UPerlinNoise::GenerateRandomVectors(int32 Seed, TArray<FVector2D>& RandomVectors)
{
	RandomVectors.SetNumUninitialized(256);

	FMath::RandInit(Seed);

	for (int32 i = 0; i < 256; i++)
	{
		float RandomAngle = FMath::DegreesToRadians(FMath::RandRange(0.0f, 360.0f));
		RandomVectors[i] = FVector2D(FMath::Cos(RandomAngle), FMath::Sin(RandomAngle));
	}
}

float UPerlinNoise::DotGridGradient(int32 Seed, int32 X, int32 Y, float XCoord, float YCoord,
	const TArray<FVector2D>& RandomVectors)
{
	int32 RandomIndex = (X * 1619 + Y * 31337) % 256;
	FVector2D RandomVector = RandomVectors[RandomIndex];
	FVector2D DistanceVector = FVector2D(XCoord, YCoord) - FVector2D(X, Y);

	return FVector2D::DotProduct(RandomVector, DistanceVector);
}

float UPerlinNoise::Interpolate(float A, float B, float X)
{	
	float InterpolatedValue = A * (1 - X) + B * X;
	return InterpolatedValue;
}

float UPerlinNoise::PerlinNoise2D(int32 Seed, float X, float Y, float Frequency, int32 Octaves, float Persistence,
	const TArray<FVector2D>& RandomVectors)
{
	float NoiseValue = 0.0f;
	float Amplitude = 1.0f;
	float MaxValue = 0.0f;

	for (int32 i = 0; i < Octaves; i++)
	{
		NoiseValue += PerlinNoise2D(Seed, X * Frequency, Y * Frequency, Frequency, Octaves, Persistence, RandomVectors) * Amplitude;
		MaxValue += Amplitude;
		Amplitude *= Persistence;
		Frequency *= 2;
	}

	return NoiseValue / MaxValue;
}

void UPerlinNoise::PrintPerlinNoise(int32 Width, int32 Height, int32 Seed, float Frequency, int32 Octaves,
	float Persistence)
{
	TArray<FVector2D> RandomVectors;
	GenerateRandomVectors(Seed, RandomVectors);

	for (int32 Y = 0; Y < Height; Y++)
	{
		for (int32 X = 0; X < Width; X++)
		{
			float NoiseValue = PerlinNoise2D(Seed, X, Y, Frequency, Octaves, Persistence, RandomVectors);
			UE_LOG(LogTemp, Warning, TEXT("Perlin Noise Value at X: %d Y: %d is %f"), X, Y, NoiseValue);
		}
	}
}




