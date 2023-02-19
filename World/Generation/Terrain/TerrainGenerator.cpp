#include "TerrainGenerator.h"

//nice hack to remember :)
namespace {
    const int biomeSeed = RandomSingleton::get().intInRange(424, 325322);
    const int heightSeed = RandomSingleton::get().intInRange(424, 325322);

//    const int biomeSeed = 58917;
//    const int heightSeed = 239544;
}

NoiseGenerator TerrainGenerator::biomeNoiseGenerator(biomeSeed * 2);
NoiseGenerator TerrainGenerator::heightMapGenerator(heightSeed);

TerrainGenerator::TerrainGenerator() :
        grassBiome(biomeSeed),
        desertBiome(biomeSeed),
        oceanBiome(biomeSeed),
        forestBiome(biomeSeed)
{
    //std::cout << biomeSeed << " " << heightSeed << std::endl;
    srand(time(NULL));
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

    const auto& pos = chunk.getPosition();
    randomEngine.setSeed((static_cast<int>(pos.x) ^ static_cast<int>(pos.x)) << 2);
    HeightMap heightMap;
    BiomeMap biomeMap;

    getBiomeMap(chunk, biomeMap);
    getHeightMap(chunk, heightMap);

    int maxHeight = *std::max(heightMap.begin(), heightMap.end());

    //water level is 64
    maxHeight = std::max(maxHeight, heightMapGenerator.getWaterLevel());
    setBlocks(chunk, maxHeight, heightMap, biomeMap);
}

int TerrainGenerator::getMinimumSpawnHeight() {
    return heightMapGenerator.getWaterLevel();
}

void TerrainGenerator::setBlocks(Chunk& chunk, int maxHeight, HeightMap& heightMap, BiomeMap& biomeMap) {
    int waterLevel = biomeNoiseGenerator.getWaterLevel();
    const auto& chunkPosition = chunk.getPosition();
    //I need to pass this empty vector to edit block

    std::vector<glm::vec3> trees;

    for(int z = chunkPosition.z; z < chunkPosition.z + chunkSize; z++) {
        for(int x = chunkPosition.x; x < chunkPosition.x + chunkSize; x++) {
            auto& biome = getBiome(x, z, biomeMap);
            int height = heightMap[z%(chunkSize-1) * chunkSize + x%(chunkSize-1)];
            for(int y = chunkPosition.y; y < chunkPosition.y + chunkSize; y++) {
                //trees
                if(y > height && y >= waterLevel) {
                    //air block
                    continue;
                }

                else {
                    if (
                            randomEngine.intInRange(0, biome.getTreeFrequency()) ==
                            5 && y >= height - 6
                            && y > waterLevel
                    ) {
                        trees.push_back({x, y + 1, z});
                    }
                    if (
                            randomEngine.intInRange(0, biome.getPlantFrequency()) == 5
                            && y >= height - 6
                            && y > waterLevel
                    ) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &biome.getFlowerBlock(randomEngine));
                        chunk.setHasWater(true);
                    }
                    else if(y > height and y < waterLevel) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &block_type::WaterBlock);
                        chunk.setHasWater(true);
                    }
                    else if(y == height && y > waterLevel) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &biome.getTopBlock(randomEngine));
                    }
                    else if(y > height - 4 && y < waterLevel) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &biome.getUnderWaterBlock(randomEngine));
                    }
                    else if(y > height - 4) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &biome.getUndergroundBlock(randomEngine));
                    }
                    else {
                        chunk.setAirStatus(false);
                        auto r = randomEngine.intInRange(0, biome.getMineralFrequency());
                        if(
                                r > 0 && r <= 20
                        ) {
                            chunk.placeBlock({x,y,z}, &biome.getMineralBlock(randomEngine));
                        }
                        else {
                            chunk.placeBlock({x,y,z}, &block_type::CobblestoneBlock);
                        }
                    }
                }
            }
        }
    }

    for(const auto& tree : trees) {
        int x = tree.x;
        int z = tree.z;

        getBiome(x, z, biomeMap).makeTree(randomEngine, chunk, x, tree.y, z);
    }

}

void TerrainGenerator::getHeightMap(Chunk& chunk, HeightMap& heightMap) {
    const auto& blocks = chunk.getBlocks();
    const auto& chunkPosition = chunk.getPosition();
    //generating a height map for same x and z positions
    for(int i = 0; i < heightMapSize; i++) {
        const auto& blockPosition = blocks[i].getPosition();
        heightMap[i] = heightMapGenerator.getHeight(blockPosition.x, blockPosition.z, chunkPosition.x, chunkPosition.z);
    }
}

void TerrainGenerator::getBiomeMap(Chunk& chunk, BiomeMap& biomeMap) {
    auto pos = chunk.getPosition();
    const auto& blocks = chunk.getBlocks();
    for(int i = 0; i < biomeMapSize; i++) {
        const auto& blockPosition = blocks[i].getPosition();
        biomeMap[i] = biomeNoiseGenerator.getHeight(blockPosition.x, blockPosition.z, pos.x + 10, pos.z + 10);
    }
}

const Biome &TerrainGenerator::getBiome(int x, int z, BiomeMap& biomeMap) const {
    int biomeValue = biomeMap[z%(chunkSize) * chunkSize + x%(chunkSize)];

    if (biomeValue > 160) {
        return oceanBiome;
    }
    else if (biomeValue > 150) {
        return grassBiome;
    }
    else if (biomeValue > 130) {
        return forestBiome;
    }
    else if (biomeValue > 110) {
        return forestBiome;
    }
    else if (biomeValue > 80) {
        return grassBiome;
    }
    else {
        return desertBiome;
    }
}
