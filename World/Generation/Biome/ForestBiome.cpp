//
// Created by tomislav on 2/17/23.
//

#include "ForestBiome.h"

ForestBiome::ForestBiome(int seed)
: Biome(getNoiseParameters(), 60, 80, seed) {}

const ChunkBlockData &ForestBiome::getTopBlock(Rand &rand) const {
    return block_type::GrassBlock;
}

const ChunkBlockData &ForestBiome::getUnderWaterBlock(Rand &rand) const {
    return rand.intInRange(0, 10) > 9
    ? block_type::GrassBlock : block_type::DirtBlock;
}

void ForestBiome::makeTree(Rand& rand, Chunk &chunk, int x, int y, int z) const {
    TreeGenerator::makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters ForestBiome::getNoiseParameters() {
    NoiseParameters heightParams;
    heightParams.octaves = 5;
    heightParams.amplitude = 100;
    heightParams.smoothness = 195; // 195
    heightParams.heightOffset = -32;
    heightParams.roughness = 0.52;

    return heightParams;
}
