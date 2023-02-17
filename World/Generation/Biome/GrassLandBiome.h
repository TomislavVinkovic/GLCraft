#pragma once

#include "Biome.h"

class GrasslandBiome : public Biome {
public:
    GrasslandBiome(int seed);

    const ChunkBlockData& getBeachBlock(Rand &rand) const override;
    const ChunkBlockData& getTopBlock(Rand &rand) const override;
    const ChunkBlockData& getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

private:
    NoiseParameters getNoiseParameters() override;
};