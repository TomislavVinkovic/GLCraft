#pragma once

#include "Biome.h"

class DesertBiome : public Biome {
public:
    DesertBiome(int seed);
    const ChunkBlockData& getTopBlock(Rand &rand) const override;
    const ChunkBlockData& getUnderWaterBlock(Rand &rand) const override;
    const ChunkBlockData& getUndergroundBlock(Rand &rand) const;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

private:
    NoiseParameters getNoiseParameters() override;
};
