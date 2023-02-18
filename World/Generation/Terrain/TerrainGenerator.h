#pragma once

#include "Generation/Biome/Biome.h"
#include "Generation/Biome/DesertBiome.h"
#include "Generation/Biome/ForestBiome.h"
#include "Generation/Biome/GrassLandBiome.h"
#include "Generation/Biome/OceanBiome.h"
#include "Chunk.h"
#include "InterpolationMaths.h"

#include <vector>
#include <array>

static const int heightMapSize = 16*16;
static const int biomeMapSize = 17*17;

typedef std::array<int, biomeMapSize> BiomeMap;
typedef std::array<int, heightMapSize> HeightMap;

class TerrainGenerator {

    public:
        TerrainGenerator();

        void generateTerrainFor(Chunk &chunk);
        int getMinimumSpawnHeight();

    private:
        //27891 //najdrazi
        //31245
        Random<std::minstd_rand> randomEngine;
        static const int chunkDimensions = 16*16*16;
        static const int chunkSize = 16;
        static NoiseGenerator biomeNoiseGenerator;
        static NoiseGenerator heightMapGenerator;

        void setBlocks(Chunk& chunk, int maxHeight, HeightMap& heightMap, BiomeMap& biomeMap);
        static void setupNoise();
        void getHeightMap(Chunk& chunk, HeightMap& heightMap);
        void getBiomeMap(Chunk& chunk, BiomeMap& biomeMap);

        const Biome &getBiome(int x, int z, BiomeMap& biomeMap) const;


        GrasslandBiome grassBiome;
        DesertBiome desertBiome;
        OceanBiome oceanBiome;
        ForestBiome forestBiome;
};
