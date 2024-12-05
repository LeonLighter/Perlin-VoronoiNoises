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
	// Générer une texture de Perlin Noise
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Noise")
	static UTexture2D* GeneratePerlinNoiseTexture(
		UPARAM(meta = (ClampMin = "1", ClampMax = "2048")) int32 Width = 256,
		UPARAM(meta = (ClampMin = "1", ClampMax = "2048")) int32 Height = 256,
		UPARAM(meta = (ClampMin = "0.01", ClampMax = "10.0")) float Scale = 1.0f,
		UPARAM(meta = (ClampMin = "1", ClampMax = "8")) int32 Octaves = 4,
		UPARAM(meta = (ClampMin = "0.0", ClampMax = "1.0")) float Persistence = 0.5f,
		UPARAM(meta = (ClampMin = "1.0", ClampMax = "4.0")) float Frequencies = 2.0f,
		UPARAM(meta = (ClampMin = "0", ClampMax = "10000")) int32 Seed = 0
	);

private:
	// Méthode utilitaire pour calculer le bruit de Perlin
	static float PerlinNoise2D(float X, float Y, int32 Seed);
    
	// Interpolation linéaire
	static float Lerp(float A, float B, float T);
    
	// Fonction de bruit pseudo-aléatoire
	static float Noise(int32 X, int32 Y, int32 Seed);
    
	// Fonction de gradient
	static float Dot(int32 Hash, float X, float Y);
};
