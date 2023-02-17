#pragma once

#include "Biome.h"

class ForestBiome : public Biome {
public:
    ForestBiome(int seed);

    //ChunkBlock getPlant(Rand &rand) const override;
    const ChunkBlockData& getTopBlock(Rand &rand) const override;
    const ChunkBlockData& getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

private:
    NoiseParameters getNoiseParameters() override;
};
