#include "PerlinNoiseUsageExample.h"
#include "PerlinNoise.h"

APerlinNoiseUsageExample::APerlinNoiseUsageExample()
{
	// Configurer l'acteur pour qu'il soit éditable dans l'éditeur
	PrimaryActorTick.bCanEverTick = false;
}

void APerlinNoiseUsageExample::GeneratePerlinNoiseTexture()
{
	// Générer la texture en utilisant la bibliothèque de bruit de Perlin
	// Sauvegarder dans le dossier Content du projet
	GeneratedNoiseTexture = UPerlinNoise::GeneratePerlinNoiseTexture(
		TextureWidth,
		TextureHeight,
		NoiseScale,
		Octaves,
		Persistence,
		Frequencies,
		Seed
	);
}

