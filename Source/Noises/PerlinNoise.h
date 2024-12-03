// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PerlinNoise.generated.h"


/**
 * étape 1 : définir une grille de 2 dimensions et attacher à chaque élément de cette grille un vecteur aléatoire
 * ce vecteur est généré grâce à une fonction de distribution uniforme qui retourne un nombre et ce nombre est projeté sur une sphère
 * étape 2 : la deuxième étape consiste pour un point N dans chaque cellule de calculer un vecteur de distance entre chaque bord de la cellule et le point
 * une fois que l'on a ce vecteur on peut calculer le produit scalaire entre ce vecteur et le vecteur aléatoire de la cellule
 * étape 3 : une fois que l'on a calculé le produit scalaire pour chaque bord de la cellule on peut interpoler ces valeurs
 * étape 4 : on utilise le système d'octave, on va définir le bruit de perlin comme n'importe quelle onde, l'axe Y va devenir l'amplitude de l'onde et l'axe X la fréquence
 * on va donc ajouter plusieurs onde de fréquence différentes et d'amplitude différentes pour obtenir un bruit de perlin plus complexe
 * étape 5 : on utilise la fonction de bruit de perlin pour générer une texture
 */
UCLASS()
class NOISES_API UPerlinNoise : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	
	//étape 1 : définir une grille de 2 dimensions et attacher à chaque élément de cette grille un vecteur aléatoire
	//ce vecteur est généré grâce à une fonction de distribution uniforme qui retourne un nombre et ce nombre est projeté sur une sphère
	UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
	static void GenerateRandomVectors(int32 Seed, TArray<FVector2D>& RandomVectors);

	//étape 2 : la deuxième étape consiste pour un point N dans chaque cellule de calculer un vecteur de distance entre chaque bord de la cellule et le point
	//une fois que l'on a ce vecteur on peut calculer le produit scalaire entre ce vecteur et le vecteur aléatoire de la cellule
	UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
	static float DotGridGradient(int32 Seed, int32 X, int32 Y, float XCoord, float YCoord, const TArray<FVector2D>& RandomVectors);

	//étape 3 : une fois que l'on a calculé le produit scalaire pour chaque bord de la cellule on peut interpoler ces valeurs
	UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
	static float Interpolate(float A, float B, float X);

	//étape 4 : on utilise le système d'octave, on va définir le bruit de perlin comme n'importe quelle onde, l'axe Y va devenir l'amplitude de l'onde et l'axe X la fréquence
	//on va donc ajouter plusieurs onde de fréquence différentes et d'amplitude différentes pour obtenir un bruit de perlin plus complexe
	UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
	static float PerlinNoise2D(int32 Seed, float X, float Y, float Frequency, int32 Octaves, float Persistence, const TArray<FVector2D>& RandomVectors);

	//étape 5 : on utilise la fonction de bruit de perlin pour générer une texture2D
	//UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
	//static UTexture2D* GeneratePerlinNoiseTexture(int32 Width, int32 Height, int32 Seed, float Frequency, int32 Octaves, float Persistence);

	//afficher le résultat du perlin noise dans la console
	UFUNCTION(BlueprintCallable, Category = "Perlin Noise")
	static void PrintPerlinNoise(int32 Width, int32 Height, int32 Seed, float Frequency, int32 Octaves, float Persistence);
};
