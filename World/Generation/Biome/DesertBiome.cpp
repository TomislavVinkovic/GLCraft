#include "DesertBiome.h"

DesertBiome::DesertBiome(int seed)
        : Biome(getNoiseParameters(), 1350, 500, seed)
{
}

const ChunkBlockData& DesertBiome::getTopBlock(Rand &rand) const
{
    return block_type::SandBlock;
}

const ChunkBlockData& DesertBiome::getUnderWaterBlock(Rand &rand) const
{
    return block_type::SandBlock;
}

void DesertBiome::makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const
{
    TreeGenerator::makeCactus(chunk, rand, x, y, z);
}

NoiseParameters DesertBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 80;
    heightParams.smoothness = 335;
    heightParams.heightOffset = -7;
    heightParams.roughness = 0.56;

    return heightParams;
}
