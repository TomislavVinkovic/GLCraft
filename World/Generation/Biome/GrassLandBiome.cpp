//
// Created by tomislav on 2/17/23.
//

#include "GrassLandBiome.h"

GrasslandBiome::GrasslandBiome(int seed)
: Biome(getNoiseParameters(), 1000, 20, seed){}

const ChunkBlockData &GrasslandBiome::getBeachBlock(Rand &rand) const {
    return rand.intInRange(0, 10) > 2
        ? block_type::GrassBlock : block_type::DirtBlock;
}

const ChunkBlockData &GrasslandBiome::getTopBlock(Rand &rand) const {
    return block_type::GrassBlock;
}

const ChunkBlockData &GrasslandBiome::getUnderWaterBlock(Rand &rand) const {
    return rand.intInRange(0, 10) > 8
        ? block_type::DirtBlock : block_type::SandBlock;
}

void GrasslandBiome::makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const {
    TreeGenerator::makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters GrasslandBiome::getNoiseParameters() {
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 85;
    heightParams.smoothness = 235;
    heightParams.heightOffset = -20;
    heightParams.roughness = 0.51;

    return heightParams;
}
