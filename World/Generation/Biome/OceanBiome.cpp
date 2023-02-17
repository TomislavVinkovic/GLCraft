//
// Created by tomislav on 2/17/23.
//

#include "OceanBiome.h"

OceanBiome::OceanBiome(int seed)
: Biome(getNoiseParameters(), 50, 100, seed){}

const ChunkBlockData &OceanBiome::getTopBlock(Rand &rand) const {
    return block_type::GrassBlock;
}

const ChunkBlockData &OceanBiome::getUnderWaterBlock(Rand &rand) const {
    return block_type::SandBlock;
}

void OceanBiome::makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const {
    return; //no tree here for now
    //TODO: ADD TREES HERE :D
}

NoiseParameters OceanBiome::getNoiseParameters() {
    NoiseParameters heightParams;
    heightParams.octaves = 7;
    heightParams.amplitude = 43;
    heightParams.smoothness = 55;
    heightParams.heightOffset = 0;
    heightParams.roughness = 0.50;

    return heightParams;
}
