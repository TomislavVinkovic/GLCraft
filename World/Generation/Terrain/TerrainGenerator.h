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

class TerrainGenerator {

    public:
        TerrainGenerator();

        void generateTerrainFor(Chunk &chunk);
        int getMinimumSpawnHeight();

    private:
        Random<std::minstd_rand> randomEngine;
        static const int chunkDimensions = 16*16*16;
        static const int chunkSize = 16;
        static const int heightMapSize = chunkSize*chunkSize;
        static const int biomeMapSize = (chunkSize+1)*(chunkSize + 1);
        static NoiseGenerator biomeNoiseGenerator;
        static NoiseGenerator heightMapGenerator;
        Chunk* genChunk;
        std::array<int, TerrainGenerator::heightMapSize> heightMap;
        std::array<int, TerrainGenerator::biomeMapSize> biomeMap;

        void setBlocks(int maxHeight);
        static void setupNoise();
        void getHeightIn(int xMin, int zMin, int xMax, int zMax);
        void getHeightMap();
        void getBiomeMap();

        const Biome &getBiome(int x, int z) const;


        GrasslandBiome grassBiome;
        DesertBiome desertBiome;
        OceanBiome oceanBiome;
        ForestBiome forestBiome;
};
