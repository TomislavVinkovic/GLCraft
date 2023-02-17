#include "TerrainGenerator.h"

//nice hack to remember :)
namespace {
    const int seed1 = RandomSingleton::get().intInRange(424, 325322);
    //const int seed2 = RandomSingleton::get().intInRange(424, 325322);
    const int seed2 = 27891;
}

NoiseGenerator TerrainGenerator::biomeNoiseGenerator(seed1 * 2);
NoiseGenerator TerrainGenerator::heightMapGenerator(seed2);

TerrainGenerator::TerrainGenerator() :
        grassBiome(seed1),
        desertBiome(seed1),
        oceanBiome(seed1),
        forestBiome(seed1)
{
    setupNoise();
}

void TerrainGenerator::setupNoise() {
    static bool noiseGen = false;
    if (!noiseGen) {
        //std::cout << "making noise\n";
        noiseGen = true;

        NoiseParameters biomeParams;
        biomeParams.octaves = 5;
        biomeParams.amplitude = 120;
        biomeParams.smoothness = 1035;
        biomeParams.heightOffset = 0;
        biomeParams.roughness = 0.75;

        biomeNoiseGenerator.setParameters(biomeParams);
    }
}

void TerrainGenerator::generateTerrainFor(Chunk &chunk) {
    genChunk = &chunk;

    const auto& pos = genChunk->getPosition();
    randomEngine.setSeed((static_cast<int>(pos.x) ^ static_cast<int>(pos.x)) << 2);

    getBiomeMap();
    getHeightMap();

    int maxHeight = *std::max(heightMap.begin(), heightMap.end());

    //water level is 64
    maxHeight = std::max(maxHeight, biomeNoiseGenerator.getWaterLevel());
    setBlocks(maxHeight);
}

int TerrainGenerator::getMinimumSpawnHeight() {
    return biomeNoiseGenerator.getWaterLevel();
}

void TerrainGenerator::setBlocks(int maxHeight) {
    int waterLevel = biomeNoiseGenerator.getWaterLevel();
    for (int y = 0; y < maxHeight + 1; y++)
        for (int x = 0; x < chunkSize; x++)
            for (int z = 0; z < chunkSize; z++) {
                int height = heightMap[x * chunkSize + z];
                auto &biome = getBiome(x, z);

                if (y > height) {
                    if (y <= waterLevel) {
                        genChunk->setHasWater(true);
                        genChunk->placeBlock({x, y, z}, &block_type::WaterBlock);
                    }
                    continue;
                }
                else if (y == height) {
                    if (y >= waterLevel) {
                        if (y < waterLevel + 4) {
                            genChunk->setAirStatus(false);
                            genChunk->placeBlock({x, y, z},&biome.getBeachBlock(randomEngine));
                            continue;
                        }
                          //I will not use trees and plants for now..
//                        if (randomEngine.intInRange(0, biome.getTreeFrequency()) ==
//                            5) {
//                            trees.emplace_back(x, y + 1, z);
//                        }
//                        if (randomEngine.intInRange(0, biome.getPlantFrequency()) ==
//                            5) {
//                            plants.emplace_back(x, y + 1, z);
//                        }
                        genChunk->setAirStatus(false);
                        genChunk->placeBlock(
                                {x, y, z},
                                &getBiome(x, z).getTopBlock(randomEngine)
                        );
                    }
                    else {
                        genChunk->setAirStatus(false);
                        genChunk->placeBlock(
                                {x, y, z},
                                &biome.getUnderWaterBlock(randomEngine)
                       );
                    }
                }
                else if (y > height - 3) {
                    genChunk->setAirStatus(false);
                    genChunk->placeBlock({x, y, z}, &block_type::DirtBlock);
                }
                else {
                    genChunk->setAirStatus(false);
                    genChunk->placeBlock({x, y, z}, &block_type::CobblestoneBlock);
                }
            }

}

void TerrainGenerator::getHeightIn(int xMin, int zMin, int xMax, int zMax) {
//    auto getHeightAt = [&](int x, int z) {
//        const Biome &biome = getBiome(x, z);
//        return biome.getHeight(x, z, genChunk->getPosition().x,
//                               genChunk->getPosition().z);
//    };
//
//    float bottomLeft = static_cast<float>(getHeightAt(xMin, zMin));
//    float bottomRight = static_cast<float>(getHeightAt(xMax, zMin));
//    float topLeft = static_cast<float>(getHeightAt(xMin, zMax));
//    float topRight = static_cast<float>(getHeightAt(xMax, zMax));
//
//    for (int x = xMin; x < xMax; ++x)
//        for (int z = zMin; z < zMax; ++z) {
//            if (x == chunkSize)
//                continue;
//            if (z == chunkSize)
//                continue;
//
//            float h = InterpolationMaths::smoothInterpolation(
//                    bottomLeft, topLeft, bottomRight, topRight,
//                    static_cast<float>(xMin), static_cast<float>(xMax),
//                    static_cast<float>(zMin), static_cast<float>(zMax),
//                    static_cast<float>(x), static_cast<float>(z));
//
//            heightMap[x * chunkSize + z] = static_cast<int>(h);
//        }
    const auto& blocks = genChunk->getBlocks();
    const auto& chunkPosition = genChunk->getPosition();
    //generating a height map for same x and z positions
    for(int i = 0; i <= 255; i++) {
        const auto& blockPosition = blocks[i].getPosition();
        heightMap[i] = heightMapGenerator.getHeight(blockPosition.x, blockPosition.z, chunkPosition.x, chunkPosition.z);
    }
}

void TerrainGenerator::getHeightMap() {
    constexpr static auto HALF_CHUNK = chunkSize / 2;
    constexpr static auto CHUNK = chunkSize;

    getHeightIn(0, 0, HALF_CHUNK, HALF_CHUNK);
    getHeightIn(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
    getHeightIn(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
    getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
}

void TerrainGenerator::getBiomeMap() {
    auto pos = genChunk->getPosition();

    for (int x = 0; x < chunkSize + 1; x++) {
        for (int z = 0; z < chunkSize + 1; z++) {
            double h = biomeNoiseGenerator.getHeight(x, z, pos.x + 10,
                                                 pos.y + 10);
            biomeMap[x * (chunkSize+1) + z] = static_cast<int>(h);
        }
    }
}

const Biome &TerrainGenerator::getBiome(int x, int z) const {
    int biomeValue = biomeMap[x * (chunkSize+1) + z];

    if (biomeValue > 160) {
        return oceanBiome;
    }
    else if (biomeValue > 150) {
        return grassBiome;
    }
    else if (biomeValue > 130) {
        return forestBiome;
    }
//    else if (biomeValue > 120) {
//        return m_temperateForest;
//    }
    else if (biomeValue > 110) {
        return forestBiome;
    }
    else if (biomeValue > 100) {
        return grassBiome;
    }
    else {
        return desertBiome;
    }
}
