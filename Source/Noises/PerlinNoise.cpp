// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinNoise.h"
#include "Engine/Texture2D.h"
#include "Math/UnrealMathUtility.h"

UTexture2D* UPerlinNoise::GeneratePerlinNoiseTexture(
    int32 Width, int32 Height, float Scale, int32 Octaves, 
    float Persistence, float Frequencies, int32 Seed)
{
    // Créer la texture 2D
    UTexture2D* NoiseTexture = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
    
    // Vérifier si la texture a été créée avec succès
    if (!NoiseTexture)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create noise texture"));
        return nullptr;
    }

    // Verrouiller la région de la texture pour l'écriture
    FTexture2DMipMap& Mip = NoiseTexture->GetPlatformData()->Mips[0];
    void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FColor* PixelPtr = static_cast<FColor*>(Data);

    // Variables pour le bruit multi-octaves
    float AmplitudeTotal = 0.0f;
    float Amplitude = 1.0f;

    // Générer le bruit de Perlin multi-octaves
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            float Noise = 0.0f;
            float Frequency = Scale;
            float CurrentAmplitude = 1.0f;

            // Calcul du bruit pour chaque octave
            for (int Octave = 0; Octave < Octaves; ++Octave)
            {
                float SampleX = x / Scale * Frequency + Seed;
                float SampleY = y / Scale * Frequency + Seed;

                // Calculer le bruit de Perlin pour cette octave
                float PerlinValue = PerlinNoise2D(SampleX, SampleY, Seed + Octave);
                
                // Ajouter la contribution de l'octave
                Noise += PerlinValue * CurrentAmplitude;

                // Mise à jour de la fréquence et de l'amplitude
                Frequency *= Frequencies;
                CurrentAmplitude *= Persistence;
            }

            // Normaliser le bruit entre 0 et 1
            Noise = (Noise + 1.0f) * 0.5f;

            // Convertir en couleur
            uint8 NoiseColor = FMath::Clamp(Noise * 255.0f, 0.0f, 255.0f);
            PixelPtr[y * Width + x] = FColor(NoiseColor, NoiseColor, NoiseColor, 255);
        }
    }

    // Déverrouiller et mettre à jour la texture
    Mip.BulkData.Unlock();
    NoiseTexture->UpdateResource();

    return NoiseTexture;
}

float UPerlinNoise::PerlinNoise2D(float X, float Y, int32 Seed)
{
    // Coordonnées de la grille
    int32 X0 = FMath::FloorToInt(X);
    int32 X1 = X0 + 1;
    int32 Y0 = FMath::FloorToInt(Y);
    int32 Y1 = Y0 + 1;

    // Interpolation
    float SX = X - X0;
    float SY = Y - Y0;

    // Vecteurs de gradient
    float N0 = Dot(Noise(X0, Y0, Seed), SX, SY);
    float N1 = Dot(Noise(X1, Y0, Seed), SX - 1, SY);
    float N2 = Dot(Noise(X0, Y1, Seed), SX, SY - 1);
    float N3 = Dot(Noise(X1, Y1, Seed), SX - 1, SY - 1);

    // Interpolation bilinéaire
    float U = SX * SX * (3.0f - 2.0f * SX);
    float V = SY * SY * (3.0f - 2.0f * SY);

    return Lerp(
        Lerp(N0, N1, U),
        Lerp(N2, N3, U),
        V
    );
}

float UPerlinNoise::Lerp(float A, float B, float T)
{
    return A + T * (B - A);
}

float UPerlinNoise::Noise(int32 X, int32 Y, int32 Seed)
{
    // Générer un nombre pseudo-aléatoire basé sur les coordonnées et la graine
    int32 Hash = (X * 374761393 + Y * 668265263 + Seed) & 0x7FFFFFFF;
    Hash = (Hash ^ (Hash >> 13)) * 1597334677;
    Hash = Hash ^ (Hash >> 16);
    
    // Normaliser entre -1 et 1
    return (Hash / 2147483647.0f) * 2.0f - 1.0f;
}

float UPerlinNoise::Dot(int32 Hash, float X, float Y)
{
    // Calculer le produit scalaire avec un vecteur de gradient
    switch (Hash & 3)
    {
        case 0:  return  X + Y;
        case 1:  return -X + Y;
        case 2:  return  X - Y;
        case 3:  return -X - Y;
        default: return 0;
    }
}







