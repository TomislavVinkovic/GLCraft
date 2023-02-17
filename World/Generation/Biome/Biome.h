#pragma once

#include "NoiseGenerator.h"
#include "Generation/Tree/TreeGenerator.h"
#include "ChunkBlock.h"
#include "Random.h"

using Rand = Random<std::minstd_rand>;
class Chunk;

struct Biome {
public:
    Biome(const NoiseParameters &parameters, int treeFreq, int plantFreq,
          int seed);
    virtual ~Biome() = default;

    //virtual const ChunkBlockData& getPlant(Rand &rand) const = 0;
    virtual const ChunkBlockData& getTopBlock(Rand &rand) const = 0;
    virtual const ChunkBlockData& getUnderWaterBlock(Rand &rand) const = 0;
    virtual const ChunkBlockData& getBeachBlock(Rand &rand) const;
    virtual void makeTree(Rand &rand, Chunk &chunk, int x, int y,
                          int z) const = 0;

    int getHeight(int x, int z, int chunkX, int chunkZ) const;
    int getTreeFrequency() const noexcept;
    int getPlantFrequency() const noexcept;

protected:
    virtual NoiseParameters getNoiseParameters() = 0;

private:
    NoiseGenerator m_heightGenerator;
    int m_treeFreq;
    int m_plantFreq;
};